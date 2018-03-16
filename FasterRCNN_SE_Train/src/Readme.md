## FasterRCNN_SpringEditon Source <img src="https://i.imgur.com/oYejfWp.png" title="Windows8" width="48">

```
# Copyright (c) Microsoft. All rights reserved.

# Licensed under the MIT license. See LICENSE.md file in the project root
# for full license information.
```

## 1. Prepare python3.5 interpreter

1. Run download_python35_loca.bat
	This scripts are based on CNTK 2.2 and Python3.5. So i provide python3.5.3 for yours.

2. Run pyrun.bat
	This script will do only setting the path of python35. Now you can run every python file on this folder.
    
## 2. How to train network using python source
**FasterRCNN_Train_SE.py** needs 2 arguments that are number of epoch and base model.
You can select base model as AlexNet, VGG16 and VGG19. Currently CNTK can not run FasterRCNN as ResNet. This script will find **class_map.txt** , **train_img_file.txt** and **train_roi_file.txt** at parent folder.

`example`
```
python35 FasterRCNN_Train_SE.py 10 AlexNet
```
## 3. How to test network for only one image.
**FasterRCNN_Test_SE.py** needs 4 arguments.(base model , weights file path , image file path , threshold).
`example`
```
python35 FasterRCNN_Test_SE.py AlexNet ../faster_rcnn_AlexNet_e2e.model ../voc2007train/000012.jpg 0.9
```

* * *

FasterRCNN_Detect_SE.py is for C++ language. This script will be converted to binary file.