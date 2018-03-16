#include<iostream>
#include<string>
#include<unordered_map>
#include<opencv2/opencv.hpp>
#include"CNTKLibrary.h"
#include"CNTKLibraryInternals.h"
#include"ispring\CV.h"
#include"ispring/Time.h"
namespace CNTK {
	static CNTK::ValuePtr CreateDenseFloat(const CNTK::NDShape& sampleShape, const std::vector<std::vector<float>>& sequences,
										   const CNTK::DeviceDescriptor& device, bool readOnly = false) {
		return CNTK::Value::Create<float>(sampleShape, sequences, device, readOnly);
	}
	static CNTK::ValuePtr CreateDenseFloat(const CNTK::NDShape& sampleShape, const std::vector<std::vector<float>>& sequences,
										   const std::vector<bool>& sequenceStartFlags, const CNTK::DeviceDescriptor& device, bool readOnly = false) {
		return CNTK::Value::Create<float>(sampleShape, sequences, sequenceStartFlags, device, readOnly);
	}
}
cv::Mat LoadResizeAndPad(std::string path, int width, int height, int pad_value , std::vector<float>& in2) {
	cv::Mat img = cv::imread(path);
	int image_w = img.cols;
	int image_h = img.rows;
	int target_w = width;
	int target_h = height;
	if (img.cols > img.rows) {
		target_h = img.rows*width / img.cols;
	} else {
		target_w = img.cols*height / img.rows;
	}
	cv::resize(img, img, cv::Size(target_w, target_h), 0, 0, cv::INTER_NEAREST);
	int top = std::max(0, (height - target_h) / 2);
	int left = std::max(0, (width - target_w) / 2);
	int bottom = height - top - target_h;
	int right = width - left - target_w;
	cv::copyMakeBorder(img, img, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(pad_value, pad_value, pad_value));
	in2.push_back(width);
	in2.push_back(height);
	in2.push_back(target_w);
	in2.push_back(target_h);
	in2.push_back(image_w);
	in2.push_back(image_h);
	return img;
}
//https://github.com/Microsoft/CNTK/blob/release/2.2/Tests/EndToEndTests/EvalClientTests/JavaEvalTest/src/Main.java
//https://github.com/Microsoft/CNTK/blob/master/bindings/common/CNTKValueExtend.i
template <typename Dtype>
class Point4f {
public:
	Dtype Point[4]; // x1 y1 x2 y2
	Point4f(Dtype x1 = 0, Dtype y1 = 0, Dtype x2 = 0, Dtype y2 = 0) {
		Point[0] = x1; Point[1] = y1;
		Point[2] = x2; Point[3] = y2;
	}
	Point4f(const float data[4]) {
		for (int i = 0; i<4; i++) Point[i] = data[i];
	}
	Point4f(const double data[4]) {
		for (int i = 0; i<4; i++) Point[i] = data[i];
	}
	Point4f(const Point4f &other) {
		memcpy(Point, other.Point, sizeof(Point));
	}
	Dtype& operator[](const unsigned int id) {
		return Point[id];
	}
	const Dtype& operator[](const unsigned int id) const {
		return Point[id];
	}

	std::string to_string() const {
		char buff[100];
		snprintf(buff, sizeof(buff), "%.1f %.1f %.1f %.1f", Point[0], Point[1], Point[2], Point[3]);
		return std::string(buff);
	}

};

template <typename Dtype>
class BBox : public Point4f<Dtype> {
public:
	Dtype confidence;
	int id;

	BBox(Dtype x1 = 0, Dtype y1 = 0, Dtype x2 = 0, Dtype y2 = 0,
		 Dtype confidence = 0, int id = 0)
		: Point4f<Dtype>(x1, y1, x2, y2), confidence(confidence), id(id) {
	}
	BBox(Point4f<Dtype> box, Dtype confidence = 0, int id = 0)
		: Point4f<Dtype>(box), confidence(confidence), id(id) {
	}

	BBox &operator=(const BBox &other) {
		memcpy(this->Point, other.Point, sizeof(this->Point));
		confidence = other.confidence;
		id = other.id;
		return *this;
	}

	bool operator<(const class BBox &other) const {
		if (confidence != other.confidence)
			return confidence > other.confidence;
		else
			return id < other.id;
	}

	std::string to_string() const {
		char buff[100];
		snprintf(buff, sizeof(buff), "cls:%3d -- (%.3f): %.2f %.2f %.2f %.2f", id,
				 confidence, this->Point[0], this->Point[1], this->Point[2], this->Point[3]);
		return std::string(buff);
	}

	std::string to_short_string() const {
		char buff[100];
		snprintf(buff, sizeof(buff), "cls:%1d -- (%.2f)", id, confidence);
		return std::string(buff);
	}
};

template <typename Dtype>
Dtype get_iou(const Point4f<Dtype> &A, const Point4f<Dtype> &B) {
	const Dtype xx1 = std::max(A[0], B[0]);
	const Dtype yy1 = std::max(A[1], B[1]);
	const Dtype xx2 = std::min(A[2], B[2]);
	const Dtype yy2 = std::min(A[3], B[3]);
	Dtype inter = std::max(Dtype(0), xx2 - xx1 + 1) * std::max(Dtype(0), yy2 - yy1 + 1);
	Dtype areaA = (A[2] - A[0] + 1) * (A[3] - A[1] + 1);
	Dtype areaB = (B[2] - B[0] + 1) * (B[3] - B[1] + 1);
	return inter / (areaA + areaB - inter);
}
template <typename Dtype>
Point4f<Dtype> bbox_transform_inv(const Point4f<Dtype>& box, const Point4f<Dtype>& delta) {
	Dtype src_w = box[2] - box[0] + 1;
	Dtype src_h = box[3] - box[1] + 1;
	Dtype src_ctr_x = box[0] + 0.5 * src_w; // box[0] + 0.5*src_w;
	Dtype src_ctr_y = box[1] + 0.5 * src_h; // box[1] + 0.5*src_h;
	Dtype pred_ctr_x = delta[0] * src_w + src_ctr_x;
	Dtype pred_ctr_y = delta[1] * src_h + src_ctr_y;
	Dtype pred_w = exp(delta[2]) * src_w;
	Dtype pred_h = exp(delta[3]) * src_h;
	return Point4f<Dtype>(pred_ctr_x - 0.5 * pred_w, pred_ctr_y - 0.5 * pred_h,
						  pred_ctr_x + 0.5 * pred_w, pred_ctr_y + 0.5 * pred_h);
	// return Point4f<Dtype>(pred_ctr_x - 0.5*(pred_w-1) , pred_ctr_y - 0.5*(pred_h-1) ,
	// pred_ctr_x + 0.5*(pred_w-1) , pred_ctr_y + 0.5*(pred_h-1));
}
template Point4f<float> bbox_transform_inv(const Point4f<float>& box, const Point4f<float>& delta);
template Point4f<double> bbox_transform_inv(const Point4f<double>& box, const Point4f<double>& delta);

void ProcessResults(long width, long height, long cls_num, long box_num,
									  const std::vector< std::vector<float> >& vClsPred,
									  const std::vector< std::vector<float> >& vROIS,
									  const std::vector< std::vector<float> >& vbboxRegr, std::vector<BBox<float> >& results) {
	for (int cls = 1; cls < cls_num; cls++) {//start at 1 to avoid background class
		std::vector<BBox<float> > bbox;
		for (int i = 0; i < box_num; i++) {
			float score = vClsPred[0][i * cls_num + cls];

			Point4f<float> roi(vROIS[0][(i * 4) + 0],
							   vROIS[0][(i * 4) + 1],
							   vROIS[0][(i * 4) + 2],
							   vROIS[0][(i * 4) + 3]);

			Point4f<float> delta(vbboxRegr[0][(i * cls_num + cls) * 4 + 0],
								 vbboxRegr[0][(i * cls_num + cls) * 4 + 1],
								 vbboxRegr[0][(i * cls_num + cls) * 4 + 2],
								 vbboxRegr[0][(i * cls_num + cls) * 4 + 3]);

			Point4f<float> box = bbox_transform_inv(roi, delta);
			box[0] = std::max(0.0f, box[0]);
			box[1] = std::max(0.0f, box[1]);
			box[2] = std::min(width - 1.f, box[2]);
			box[3] = std::min(height - 1.f, box[3]);

			bbox.push_back(BBox<float>(box, score, cls));
		}
		sort(bbox.begin(), bbox.end());
		std::vector<bool> select(box_num, true);
		float test_score_thresh = 0.4;
		float test_nms = 0.4;
		for (int i = 0; i < box_num; i++) {
			if (select[i]) {
				if (bbox[i].confidence < test_score_thresh) break;
				for (int j = i + 1; j < box_num; j++) {
					if (select[j]) {
						if (get_iou(bbox[i], bbox[j]) > test_nms) {
							select[j] = false;
						}
					}
				}
				results.push_back(bbox[i]);
			}
		}
	}
}


int main() {
	try {
		CNTK::DeviceDescriptor device = CNTK::DeviceDescriptor::UseDefaultDevice();
		std::wstring model_path = L"../../faster_rcnn_eval_VGG16_e2e_native.model";
		std::string img_path = "C:/Users/spring/Desktop/FasterRCNN_folder/05/CNTK/PretrainedModels/CNTK-Samples-2-2/Examples/Image/DataSets/MyDataSet/testImages/0068.jpg";
		CNTK::FunctionPtr model = CNTK::Function::Load(model_path, device);
		
		std::vector<CNTK::Variable> input_vars = model->Arguments();
		std::vector<CNTK::Variable> output_vars = model->Outputs();

		CNTK::NDShape input_shape = input_vars[0].Shape();
		int image_width = input_shape.Dimensions()[0];
		int image_height = input_shape.Dimensions()[1];
		int image_channel = input_shape.Dimensions()[2];
		int image_size = input_shape.TotalSize();


		for (int i = 0; i < 10; i++) {
			
			std::vector<float> in2;

			cv::Mat img = LoadResizeAndPad(img_path, image_width, image_height, 114, in2);
			std::vector<float> float_vec;
			for (int c = 0; c < img.channels(); c++) {
				for (int h = 0; h < img.rows; h++) {
					for (int w = 0; w < img.cols; w++) {
						cv::Scalar color = img.at<cv::Vec3b>(h, w);
						if (c == 0) {
							float_vec.push_back(color[0]);
						} else if (c == 1) {
							float_vec.push_back(color[1]);
						} else {
							float_vec.push_back(color[2]);
						}
					}
				}
			}
			std::vector<std::vector<float>> float_vec2;
			float_vec2.push_back(float_vec);
			CNTK::ValuePtr input_val = CNTK::CreateDenseFloat(input_shape, float_vec2, device);
			std::unordered_map<CNTK::Variable, CNTK::ValuePtr> input_data_map;
			input_data_map.insert(std::make_pair(input_vars[0], input_val));
			//prepare input2
			CNTK::ValuePtr input_val2 = CNTK::Value::CreateBatch(input_vars[1].Shape(), in2, device);
			input_data_map.insert(std::make_pair(input_vars[1], input_val2));

			CNTK::ValuePtr output_val;

			std::unordered_map<CNTK::Variable, CNTK::ValuePtr> output_data_map;
			//output_data_map.insert(std::make_pair(output_vars[0], output_val));
			//CNTK::NDShape outputShape1 = output_vars[0].Shape();
			//CNTK::NDShape outputShape2 = output_vars[1].Shape();
			//CNTK::NDShape outputShape3 = output_vars[2].Shape();
			CNTK::ValuePtr outputValue1;
			CNTK::ValuePtr outputValue2;
			CNTK::ValuePtr outputValue3;
			output_data_map[output_vars[0]] = outputValue1;
			output_data_map[output_vars[1]] = outputValue2;
			output_data_map[output_vars[2]] = outputValue3;

			ispring::Timer::Tick("detection");
			model->Forward(input_data_map, output_data_map, device);
			std::cout << ispring::Timer::Tock("detection").curr << std::endl;


			//std::vector<std::vector<float>> output_buffer;
			//output_data_map[output_var].get()->CopyVariableValueTo<float>(input_var, output_buffer);
			std::vector< std::vector<float> > vClsPred;
			std::vector< std::vector<float> > vROIS;
			std::vector< std::vector<float> > vbboxRegr;
			output_data_map[output_vars[0]]->CopyVariableValueTo(output_vars[0], vClsPred);//1cls_pred - the class probabilities for each ROI
			output_data_map[output_vars[1]]->CopyVariableValueTo(output_vars[1], vROIS);//rpn_rois - the absolute pixel coordinates of the candidate rois
			output_data_map[output_vars[2]]->CopyVariableValueTo(output_vars[2], vbboxRegr);//bbox_regr - the regression coefficients per class for each ROI

			int cls_num = 2;
			long nSize = vbboxRegr[0].size() / cls_num / 4;
			int box_num = 300;
			//not sure about this
			if (nSize < box_num) {
				box_num = nSize;
			}
			std::vector<BBox<float>> results;
			ProcessResults(850, 850, cls_num, box_num, vClsPred, vROIS, vbboxRegr, results);
			//iterate through the actual rectangles below

			cv::Mat out_img = cv::imread(img_path);
			float scale = 850.0 / std::max(out_img.cols, out_img.rows);
			int pad = (std::max(out_img.cols, out_img.rows) - std::min(out_img.cols, out_img.rows)) / 2;
			for (std::vector<BBox<float> >::iterator i = results.begin(); i != results.end(); ++i) {
				i->id;//category
				i->confidence;
				i->Point[0] /= scale;//left
				i->Point[1] /= scale;//top
				i->Point[2] /= scale;//right
				i->Point[3] /= scale;//bottom
				if (out_img.cols > out_img.rows) {
					i->Point[1] -= pad;
					i->Point[3] -= pad;
				} else {
					i->Point[0] -= pad;
					i->Point[2] -= pad;
				}
				std::cout << "(" << i->id << "," << i->confidence << ") [" << i->Point[0] << "," << i->Point[1] << "," << i->Point[2] << "," << i->Point[3] << "]\n";
				cv::Rect rect;
				rect.x = i->Point[0];
				rect.y = i->Point[1];
				rect.width = i->Point[2] - rect.x;
				rect.height = i->Point[3] - rect.y;
				cv::rectangle(out_img, rect, cv::Scalar(0, 0, 255));
			}
			



			/*cv::Mat out_img = cv::imread(img_path);
			float scale = 850.0 / std::max(out_img.cols, out_img.rows);
			int pad = (std::max(out_img.cols, out_img.rows) - std::min(out_img.cols, out_img.rows)) / 2;
			for (int i = 0; i <vROIS[0].size()/2; i++) {
				if (vClsPred[0][i * 2 + 1] > 0.90) {
					int x1 = vROIS[0][i * 4+0] / scale;
					int y1 = vROIS[0][i * 4+1] / scale;
					int x2 = vROIS[0][i * 4+2] / scale;
					int y2 = vROIS[0][i * 4+3] / scale;
					if (out_img.cols > out_img.rows) {
						y1 -= pad;
						y2 -= pad;
					} else {
						x1 -= pad;
						x2 -= pad;
					}

					cv::Rect rect;
					rect.x = x1;
					rect.y = y1;
					rect.width = x2 - x1;
					rect.height = y2 - y1;
					cv::rectangle(out_img, rect, cv::Scalar(0, 0, 255));
					std::cout << "[" << vROIS[0][i * 4] << "," << vROIS[0][i * 4 + 1] << "," << vROIS[0][i * 4 + 2] << "," << vROIS[0][i * 4 + 3] << "]\n";
					std::cout << "(" << vClsPred[0][i * 2] << "," << vClsPred[0][i * 2 + 1] << ")\n";
				}
			}
			ispring::Image::DisplayImage(out_img);*/
			
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
