// dllmain.cpp: DLL 응용 프로그램의 진입점을 정의합니다.
#include <Windows.h>
#include<string>
#include<iostream>
#include"FasterRCNN_SE.h"

int main() {
	std::string model_path = "faster_rcnn_eval_VGG16_e2e.model";
	std::string class_map_path = "class_map.txt";
	FasterRCNN detector;

	detector.Create(model_path, class_map_path);

	std::string img_file = "0067.jpg";

	std::vector<BoxSE> boxes = detector.Detect(img_file, 0.9F);
	cv::Mat img = cv::imread(img_file);
	for (auto&box : boxes) {
		std::cout << box.m_class << std::endl;
		std::cout << box.m_score << std::endl;
		std::cout << box.m_class_name << "[" << box.x << "," << box.y << "," << box.width << "," << box.height << "]" << std::endl;
		cv::rectangle(img, box, cv::Scalar(0, 0, 255), 2);
	}
	cv::imshow("result", img);
	cv::waitKey();
	cv::destroyAllWindows();

	detector.Release();
	return 0;
}