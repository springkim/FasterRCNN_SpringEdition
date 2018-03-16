# FasterRCNN_SpringEdition <img src="https://i.imgur.com/oYejfWp.png" title="Windows8" width="48">

###### FasterRCNN C++ library. (Train,Detect both)
* All dependencies are included.
* Can train FasterRCNN as double click.
* You need only 1 header file, To detect by FasterRCNN.

<img src="https://i.imgur.com/ElCyyzT.png" title="Windows8" width="48"><img src="https://i.imgur.com/O5bye0l.png" width="48">
## Lastest news
**2018-03-15.** : Fix python process leak. Decrease exe file size.

**2017-11-14.** : Remove unuseful information(e.g. DeviceSelector)

**2017-10-14.** : Support unicode(korean) path. Changed default IPC buffers as 10000 bytes.

## Setup for train

#### 1. Download model and files.
There is a **download_VGG16.bat** , **download_VGG19.bat** and **download_AlexNet.bat** in [CNTK/FasterRCNN/](https://github.com/springkim/FasterRCNN_SpringEdition/tree/master/FasterRCNN_SE_Train).
This file can download **VGG16_ImageNet_Caffe.model**.

And run **download_bin.bat**.
This file download **FasterRCNN_Train_SE.exe** and dependency dlls.

**FasterRCNN_train_SE.exe** needs 2 argument that are number of epoch and base model name. Now you can run **train.bat**.
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
You can see [CNTK/FasterRCNN/train_img_file.txt](https://github.com/springkim/FasterRCNN_SpringEdition/blob/master/FasterRCNN_SE_Train/train_img_file.txt) to understand.
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
Run both **download_3rdparty.bat** ,**download_voc2007train** and **download_pretrained_model.bat** in the [FasterRCNN_SE_Detection](https://github.com/springkim/FasterRCNN_SpringEdition/tree/master/FasterRCNN_SE_Detection).

#### 2. Run.

And open **FasterRCNN_SE_Detection_Example.sln** as [Visual Studio 2015](https://www.visualstudio.com/ko/downloads/?rr=https%3A%2F%2Fwww.google.co.kr%2F).~~(Maybe it works on VS2013 and VS2017 too)~~

We needs only 1 header file (**FasterRCNN_SE.h**) for detect. Of course your exe file needs **FasterRCNN_Detect_SE.exe** and requirement dll(cudnn64_6.dll).

Model loading time is about 20~30s.
Detection time is about 0.15s.(7FPS)
###### Result of voc2007valid
```
aeroplane
        Recall : 0.673434
        Precision : 0.719298
bicycle
        Recall : 0.53223
        Precision : 0.618873
bird
        Recall : 0.553367
        Precision : 0.575155
boat
        Recall : 0.325579
        Precision : 0.382733
bottle
        Recall : 0.271551
        Precision : 0.327751
bus
        Recall : 0.511315
        Precision : 0.545872
car
        Recall : 0.592057
        Precision : 0.727606
cat
        Recall : 0.608507
        Precision : 0.630208
chair
        Recall : 0.201738
        Precision : 0.277222
cow
        Recall : 0.403546
        Precision : 0.541198
diningtable
        Recall : 0.364155
        Precision : 0.376712
dog
        Recall : 0.653623
        Precision : 0.681884
horse
        Recall : 0.70719
        Precision : 0.742375
motorbike
        Recall : 0.615479
        Precision : 0.686429
person
        Recall : 0.613302
        Precision : 0.740406
pottedplant
        Recall : 0.231086
        Precision : 0.269577
sheep
        Recall : 0.515167
        Precision : 0.650926
sofa
        Recall : 0.419326
        Precision : 0.428191
train
        Recall : 0.683333
        Precision : 0.748175
tvmonitor
        Recall : 0.368519
        Precision : 0.388889
```

## Reference

The class `FasterRCNN` that in `FasterRCNN_SE.h` has **3** method.
```cpp
void FasterRCNN::Create(int base_model,std::string model_path,std::string classfile,DWORD size=6000)
```
This method load trained model and class naming file.
* Parameter
	* **base_model** : You can put below values.
		* FasterRCNN::AlexNet
		* FasterRCNN::VGG16
		* FasterRCNN::VGG19
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

## TODO
- [ ] : Support simple image pass for detect.
