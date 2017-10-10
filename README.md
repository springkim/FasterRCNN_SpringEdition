# FasterRCNN_SpringEdition <img src="https://i.imgur.com/oYejfWp.png" title="Windows8" width="48">

###### FasterRCNN C++ library. (Train,Detect both)
* All dependencies are included.
* Can train FasterRCNN as double click.
* You need only 1 header file, To detect by FasterRCNN.

<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48"><img src="https://i.imgur.com/O5bye0l.png" width="48">

## Setup for train
#### 1. Download model and files.
There is a **download_model.bat** in [CNTK/FasterRCNN/](https://github.com/springkim/FasterRCNN_SpringEdition/tree/master/CNTK/FasterRCNN).
This file can download **VGG16_ImageNet_Caffe.model** .

And move to [CNTK/FasterRCNN/bin](https://github.com/springkim/FasterRCNN_SpringEdition/tree/master/CNTK/FasterRCNN/bin) and run **download_runfile.bat**.
This file download **FasterRCNN_Train_SE.exe** and dependency dlls.

**FasterRCNN_train_SE.exe** needs 1 integer argument. This argument is epoch for train.
The example run script is in [CNTK/FasterRCNN/](https://github.com/springkim/FasterRCNN_SpringEdition/tree/master/CNTK/FasterRCNN)**train.bat**.

#### 2. Train our own data format and location.

Actually, **FasterRCNN_Train_SE.exe** read only two files. first one is `../train_img_file.txt`, Second one is `../train_roi_file.txt`. That's why i made **FasterRCNN_Train_SE.exe** in **bin** folder.

This format follows the [Microsoft/CNTK](https://github.com/Microsoft/CNTK) format.

`train_img_file.txt` follows the format below.
```
0	<image-path>	0
1	<image-path>	0
2	<image-path>	0
```
First column is index of image. Second column is image path. Last column must be zero.
You can see [CNTK/FasterRCNN/train_img_file.txt](https://github.com/springkim/FasterRCNN_SpringEdition/blob/master/CNTK/FasterRCNN/train_img_file.txt) to understand.
`train_roi_file.txt` follows the format below.
```
0 |roiAndLabel <x1 y1 x2 y2 class>
1 |roiAndLabel <x1 y1 x2 y2 class> <x1 y1 x2 y2 class>
```
First column is index of image ~~(stupid format)~~ , Second column must be `|roiAndLabel` ,Third column is coordinate of object. You can write multiple coordinate of object in same line.

Finally, It looks like below.
```
┌ bin
│  ├ FasterRCNN_Train_SE.exe
│  └ <Requirement dlls>
├ img
│  └ <images that wrote in train_img_file.txt>
├ train_img_file.txt
├ train_roi_file.txt
├ VGG16_ImageNet_Caffe.model
└ train.bat
```
Now you can run **train.bat** for trainning.

model file will generate at the same location.

## Setup for detect
#### 1. Download pre-trained model and files.
Run both **download_detect_exe.bat** and **download_pretrained_model.bat** in the [FasterRCNN_SE_Detection_Example](https://github.com/springkim/FasterRCNN_SpringEdition/tree/master/FasterRCNN_SE_Detection_Example).

#### 2. Run.

And open **FasterRCNN_SE_Detection_Example.sln** as [Visual Studio 2015](https://www.visualstudio.com/ko/downloads/?rr=https%3A%2F%2Fwww.google.co.kr%2F).~~(Maybe it works on VS2013 and VS2017 too)~~

We needs only 1 header file (**FasterRCNN_SE.h**) for detect. Of course your exe file needs **FasterRCNN_Detect_SE.exe** and requirement dlls(22 files).

Model loading time is about 20~30s.
Detection time is about 0.15s.
###### Result
```
Selected GPU[0] GeForce GTX 1080 as the process wide default device.
Loading time : 27.2435
Recall : 0.759259
Precision : 0.851852
Average detection time : 0.14047
FPS : 7.11894
```
![](https://i.imgur.com/bQ8l6ae.jpg)

## Reference

The class `FasterRCNN` that in `FasterRCNN_SE.h` has **3** method.
```cpp
void FasterRCNN::Create(std::string model_path,std::string classfile,DWORD size=6000)
```
This method load trained model and class naming file.
* Parameter
	* **model_path** : trained model path (e.g. "faster_rcnn_eval_VGG16_e2e.model")
	* **classfile** : class naming file path(same as used at training)
	* **size** : IPC buffer size.(@see Technical issue)

```cpp
std::vector<BoxSE> FasterRCNN::Detect(std::string img_path, float threshold)
```
This method is detecting objects of file .
* Parameter
	* **img_path** : image path
	* **threshold** : It removes predictive boxes if there score is less than threshold.

```cpp
void FasterRCNN::Release()
```
Release main-memory and gpu-memory.



## Technical issue
The [CNTK](https://github.com/Microsoft/CNTK) is python wrapper. They support C++ interface. But it works only in CPU to detection.

[CPU version detection](https://github.com/springkim/FasterRCNN_SpringEdition/blob/master/dev/CNTK-eval-CPU-only.cpp)

I have to run this code on C++ without Python dependencies.

So, I used IPC with python executable file. I used [pyinstaller](http://www.pyinstaller.org/) for make exe file.

Finally, It does not support GPU SLI.

I tested it on (Windows10,GTX1080) and (windows10,TITAN X).

## Software requirement
* Visual Studio 2015
* CUDA 8.0
* **if you want rebuild**
	* python 3.5(Anaconda)
	* pyinstaller
	* CNTK

## Hardware requirement
* Detect
	* Main Memory : 4.5GB over
	* GPU Memory : 3GB over
* Train
	* Main Memory : 4.5GB over
	* GPU Memory : 4.5GB over


## Error
```
ValueError: attempt to get argmax of an empty sequence
```
This error means can't load roi data.
case 1 : roi data is empty.
case 2 : x2 is greater than x1 or y2 is greater than y1 in roi file.


