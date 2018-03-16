#include <Windows.h>
#include<string>
#include<iostream>
#include"ispring/All.h"	//@see https://github.com/springkim/ISpring
#include"FasterRCNN_SE.h"
std::vector<BoxSE> GetGroundTruth(std::string file) {
	std::vector<BoxSE> boxes;
	std::string tsp = file.substr(0, file.find_last_of('.')) + ".tsp";
	std::fstream fin(tsp, std::ios::in);
	while (fin.eof() == false) {
		std::string line;
		std::getline(fin, line);
		if (line.length() == 0)break;
		std::istringstream iss(line);
		BoxSE box;
		cv::RotatedRect rrect;
		iss >> box.m_class >> rrect.center.x >> rrect.center.y >> rrect.size.width >> rrect.size.height >> rrect.angle;
		box.m_class++;
		cv::Rect rect = rrect.boundingRect();
		box.x = rect.x;
		box.y = rect.y;
		box.width = rect.width;
		box.height = rect.height;
		boxes.push_back(box);
	}
	return boxes;
}
int main() {
	std::string model_path = "../../faster_rcnn_eval_VGG16_e2e_epoch(100).model";
	std::string class_map_path = "../../class_map.txt";
	
	FasterRCNN detector;
	detector.Create(FasterRCNN::VGG16,model_path, class_map_path);					//Model loading

	std::vector<std::string> files = ispring::File::FileList("../../voc2007valid", "*.jpg");
	std::map<int, std::pair<float, float>> RP;
	int cnt[21] = { 0 };
	for (int i = 1; i <= 20; i++) {
		RP.insert(std::make_pair(i, std::make_pair(0.0F, 0.0F)));
	}

	for(size_t i=0;i<files.size();i++) {
		auto file = files[i];
		std::vector<BoxSE> boxes = detector.Detect(file, 0.5F);		//Detect
		std::vector<BoxSE> ground_truth = GetGroundTruth(file);
		for (auto&gt : ground_truth) {
			gt.m_class_name = detector.GetObjectName(gt.m_class);
		}
		std::map<int,std::pair<float, float>> lRP = ispring::CVEval::GetRecallPrecisionMultiClass(ground_truth, boxes,0.5F);
		for (auto&lrp : lRP) {
			RP.find(lrp.first)->second.first += lrp.second.first;
			RP.find(lrp.first)->second.second += lrp.second.second;
			cnt[lrp.first]++;
		}
		system("cls");
		for (int i = 1; i <= 20; i++) {
			std::cout << detector.GetObjectName(i) << std::endl;
			if (cnt[i] != 0) {
				std::cout << "\tRecall : " << RP.find(i)->second.first / cnt[i] << std::endl;
				std::cout << "\tPrecision : " << RP.find(i)->second.second / cnt[i] << std::endl;
			}
		}
		/*cv::Mat img = cv::imread(file);
		for (auto&box : boxes) {
			ispring::CVEval::DrawBoxSE(img, box,cv::Scalar(0,0,255));
		}
		for (auto&box : ground_truth) {
			ispring::CVEval::DrawBoxSE(img, box,cv::Scalar(0,255,0));
		}
		cv::imshow("result", img);
		cv::waitKey(0);*/
	}
	cv::destroyAllWindows();
	detector.Release();												//Release
	

	return 0;
}