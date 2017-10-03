/*
*  FasterRCNN_SE.hpp
*  FasterRCNN_SE
*
*  Created by kimbom on 2017. 10. 2...
*  Copyright 2017 Sogang Unuv. All rights reserved.
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
class FasterRCNN {
public:
	class Box : public cv::Rect{
	public:
		int m_class;
		float m_score;
	};
private:
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
public:
	void Create(std::string model_path,DWORD size=6000) {
		m_key_shmem = this->GetKey() + "_shmem";
		m_key_mutex = this->GetKey() + "_mutex";
		m_size = size;
		
		m_mutex = ::CreateMutexA(nullptr, FALSE, m_key_mutex.c_str());
		m_shmem = ::CreateFileMappingA(INVALID_HANDLE_VALUE, nullptr,PAGE_READWRITE, 0, m_size, m_key_shmem.c_str());
		m_buffer = (char*)::MapViewOfFile(m_shmem, FILE_MAP_ALL_ACCESS, 0, 0, m_size);
		m_buffer[0] = 0;
		std::string exec = "python \"C:/Users/spring/Documents/SourceTree/FasterRCNN_SpringEdition/CNTK/FasterRCNN/src/FasterRCNN_Detect_SE.py\"";
		//std::string exec = "FasterRCNN_Detect_SE.exe";
		std::ostringstream oss;
		oss << exec << " " << m_key_shmem << " " << m_key_mutex << " " << m_size << " " << "\"" << model_path << "\"";
		UINT ret=WinExec(oss.str().c_str(), SW_SHOW);
		if (ret < 31) {
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
	std::vector<Box> Detect(std::string img_path, float threshold) {
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
		std::vector<Box> boxes;
		for (int i = 0; i < result[0]; i++) {
			Box box;
			box.m_class = result[i * 6 + 1];
			box.m_score = result[i * 6 + 2] / 10000.0;
			box.x= result[i * 6 + 3];
			box.y = result[i * 6 + 4];
			box.width = result[i * 6 + 5] - box.x;
			box.height = result[i * 6 + 6] - box.y;
			if (box.m_score >= threshold) {
				boxes.push_back(box);
			}
		}
		auto IOU = [](Box& a, Box& b)->float {
			float i = (a & b).area();
			float u = a.area() + b.area() - i;
			return i / u;
		};
		//Sort by Greater
		std::sort(boxes.begin(), boxes.end(), [](Box& a, Box& b)->bool {return a.m_score > b.m_score; });
		std::vector<bool> select(boxes.size(), true);
		std::vector<Box> boxes2;
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

		return boxes2;
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