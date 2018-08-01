/*
*  FasterRCNN_SE.h
*  FasterRCNN_SpringEdition
*
*  Created by kimbom on 2017. 10. 2...
*  Copyright 2017 Sogang Univ. All rights reserved.
*
*/
#if !defined(FASTERRCNN_SE_7E1_A_2_FASTERRCNN_SE_HPP_INCLUDED)
#define FASTERRCNN_SE_7E1_A_2_FASTERRCNN_SE_HPP_INCLUDED
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<Windows.h>
#include<opencv2/opencv.hpp>
#ifndef  SPRING_EDITION_BOX
#define SPRING_EDITION_BOX
/**
*	@brief 이 클래스는 cv::Rect를 확장한 것으로 클래스값과 스코어값이 추가되었습니다.
*	@author kimbomm
*	@date 2017-10-05
*
*	@see	https://github.com/springkim/FasterRCNN_SpringEdition
*	@see	https://github.com/springkim/YOLOv2_SpringEdition
*/
class BoxSE : public cv::Rect {
public:
	int m_class = -1;
	float m_score = 0.0F;
	std::string m_class_name;
	BoxSE() {
		m_class_name = "Unknown";
	}
	BoxSE(int c, float s, int _x, int _y, int _w, int _h, std::string name = "")
		:m_class(c), m_score(s) {
		this->x = _x;
		this->y = _y;
		this->width = _w;
		this->height = _h;
		char* lb[5] = { "th","st","nd","rd","th" };
		if (name.length() == 0) {
			m_class_name = std::to_string(m_class) + lb[m_class < 4 ? m_class : 4] + " class";
		}
	}
};
#endif
class FasterRCNN {
public:
	static const int AlexNet = 0;
	static const int VGG16 = 1;
	static const int VGG19 = 2;
private:
	int m_base_model;
	std::string m_key_mutex = "";
	HANDLE	m_mutex = INVALID_HANDLE_VALUE;
	std::string m_key_shmem = "";
	HANDLE	m_shmem = INVALID_HANDLE_VALUE;
	DWORD m_size = 0;
	char* m_buffer = nullptr;
	//0(48) = load model
	//1(49) = send image path
	//2(50) = detect
	//3(51) = receive
	//9(57) = terminate signal
	std::vector<std::string> m_class_map;
public:
	void Create(int base_model, std::string model_path,std::string classfile,DWORD size=10000,float filter_threshold=0.4F) {
		m_base_model = base_model;
		m_key_shmem = this->GetKey() + "_shmem";
		m_key_mutex = this->GetKey() + "_mutex";
		m_size = size;
		
		m_mutex = ::CreateMutexA(nullptr, FALSE, m_key_mutex.c_str());
		m_shmem = ::CreateFileMappingA(INVALID_HANDLE_VALUE, nullptr,PAGE_READWRITE, 0, m_size, m_key_shmem.c_str());
		m_buffer = (char*)::MapViewOfFile(m_shmem, FILE_MAP_ALL_ACCESS, 0, 0, m_size);
		m_buffer[0] = 0;
#ifdef FasterRCNN_SE_Test
		char* pyfile_r = "../../../FasterRCNN_SE_Train/src/FasterRCNN_Detect_SE.py";
		char _pyfile_a[MAX_PATH] = { 0 };
		GetFullPathNameA(pyfile_r, MAX_PATH, _pyfile_a, NULL);
		std::string pyfile_a = _pyfile_a;
		std::replace(pyfile_a.begin(), pyfile_a.end(), '\\', '/');
		std::string exec = "python35 \"" + pyfile_a + "\"";
#else
		std::string exec = "FasterRCNN_Detect_SE.exe";
#endif
		
		HWND hwnd = GetForegroundWindow();
		std::vector<std::string> models = { "AlexNet","VGG16","VGG19" };
		std::ostringstream oss;
		//oss << exec << " " << m_key_shmem << " " << m_key_mutex << " " << m_size << " " << "\"" << model_path << "\"" << " " << filter_threshold << " " << hwnd << " " << models[m_base_model];
		//UINT ret=WinExec(oss.str().c_str(), SW_HIDE);
		oss << m_key_shmem << " " << m_key_mutex << " " << m_size << " " << "\"" << model_path << "\"" << " " << filter_threshold << " " << hwnd << " " << models[m_base_model];
		HINSTANCE ret=ShellExecuteA(NULL, "open", exec.c_str(), oss.str().c_str(), NULL, SW_HIDE);
		if ((size_t)ret < 31) {
			::MessageBoxA(nullptr, "FasterRCNN Detector execute failed\nIt needs \"FasterRCNN_Detect_SE.exe\".", "Error", MB_OK);
			exit(1);
		}
		bool load = false;
		while (load==false) {
			WaitForSingleObject(m_mutex, INFINITE);
			if (m_buffer[0] == '1') {
				load = true;
			}
			::ReleaseMutex(m_mutex);
		}
		std::fstream fin;
		fin.open(classfile, std::ios::in);
		if (fin.is_open() == false) {
			::MessageBoxA(nullptr, "Can't read class map file", "Error", MB_OK);
			exit(1);
		}
		std::string line;
		while (!fin.eof()) {
			std::getline(fin, line);
			if (line.length() == 0) {
				break;
			}
			std::istringstream iss(line);
			std::string _class;
			iss >> _class;
			m_class_map.push_back(_class);
		}
		fin.close();
	}
	void Release() {
		bool pass = false;
		while (pass == false) {
			WaitForSingleObject(m_mutex, INFINITE);
			if (m_buffer[0] == '1') {
				m_buffer[0] = '9';
				pass = true;
			}
			::ReleaseMutex(m_mutex);
		}
		::UnmapViewOfFile(m_buffer);
		::CloseHandle(m_shmem);
		::ReleaseMutex(m_mutex);
		m_shmem = INVALID_HANDLE_VALUE;
		m_mutex = INVALID_HANDLE_VALUE;
	}
	~FasterRCNN() {
		if (m_shmem != INVALID_HANDLE_VALUE) {
			this->Release();
		}
	}
	std::vector<BoxSE> Detect(std::string img_path, float threshold) {
		::ReleaseMutex(m_mutex);
		bool pass = false;
		while (pass == false) {
			WaitForSingleObject(m_mutex, INFINITE);
			if (m_buffer[0] == '1') {
				memset(m_buffer + 1, 0,m_size - 1);
				char* p = m_buffer + 1;
				const char* q = img_path.data();
				while (*q != '\0') {
					*p++ = *q++;
				}
				*p = '\0';
				//strcpy(m_buffer + 1, img_path.c_str());	//strcpy is not working on SDL.
				//strcpy_s(m_buffer + 1, m_size-1,img_path.c_str());		//strcpy_s is not working on debug mode.
				m_buffer[0] = '2';	//running
				pass = true;
			}
			::ReleaseMutex(m_mutex);
		}
		std::string receive;
		bool finish = false;
		while (finish == false) {
			WaitForSingleObject(m_mutex, INFINITE);
			if (m_buffer[0] == '3') {
				receive = m_buffer + 1;
				m_buffer[0] = '1';	//restore
				finish = true;
			}
			::ReleaseMutex(m_mutex);
		}
		std::string token = ";";
		std::string::size_type offset = 0;
		std::vector<int> result;
		while (offset<receive.length()) {
			std::string str = receive.substr(offset, receive.find(token, offset) - offset);
			result.push_back(atoi(str.c_str()));
			offset += str.length() + 1;
		}
		std::vector<BoxSE> boxes;
		for (int i = 0; i < result[0]; i++) {
			BoxSE box;
			box.m_class = result[i * 6 + 1];
			box.m_class_name = m_class_map[box.m_class];
			box.m_score = result[i * 6 + 2] / 10000.0F;
			box.x= result[i * 6 + 3];
			box.y = result[i * 6 + 4];
			box.width = result[i * 6 + 5] - box.x;
			box.height = result[i * 6 + 6] - box.y;
			if (box.m_score >= threshold) {
				boxes.push_back(box);
			}
		}
		auto IOU = [](BoxSE& a, BoxSE& b)->float {
			float i = static_cast<float>((a & b).area());
			float u = a.area() + b.area() - i;
			return i / u;
		};
		//Sort by Greater
		std::sort(boxes.begin(), boxes.end(), [](BoxSE& a, BoxSE& b)->bool {return a.m_score > b.m_score; });
		std::vector<bool> select(boxes.size(), true);
		std::vector<BoxSE> boxes2;
		for (int i = 0; i < boxes.size(); i++) {
			if (select[i] == true) {
				for (int j = i + 1; j < boxes.size(); j++) {
					if (select[j] == true) {
						if (IOU(boxes[i], boxes[j]) > 0.4) {
							select[j] = false;
						}
					}
				}
				boxes2.push_back(boxes[i]);
			}
		}
		WaitForSingleObject(m_mutex, INFINITE);
		return boxes2;
	}
	std::string GetObjectName(int idx) {
		return m_class_map[idx];
	}
private:
	std::string GetKey() {
		//https://stackoverflow.com/questions/10654258/get-millisecond-part-of-time
		SYSTEMTIME stime;
		FILETIME ftime;
		FILETIME ftime_stamp;
		GetSystemTimeAsFileTime(&ftime_stamp);
		FileTimeToLocalFileTime(&ftime_stamp, &ftime);
		FileTimeToSystemTime(&ftime, &stime);
		char buf[256];
		sprintf_s(buf, "%d%d%d%d%d%d%d", stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
		return buf;
	}
};
#endif  //FASTERRCNN_SE_7E1_A_2_FASTERRCNN_SE_HPP_INCLUDED