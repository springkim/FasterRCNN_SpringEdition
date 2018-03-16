import os
import sys
import time
import numpy as np
import cv2
import re
import mmap
import win32event
import win32con
from cntk import load_model
from utils.config_helpers import merge_configs
import utils.od_utils as od
from utils.FasterRCNN_eval import FasterRCNN_Evaluator

def get_configuration_vgg16():
    # load configs for detector, base network and data set
    from utils.configs.FasterRCNN_config import cfg as detector_cfg
    from utils.configs.VGG16_config import cfg as network_cfg
    from user_config import cfg as dataset_cfg
    return merge_configs([detector_cfg, network_cfg, dataset_cfg])
def get_configuration_vgg19():
    # load configs for detector, base network and data set
    from utils.configs.FasterRCNN_config import cfg as detector_cfg
    from utils.configs.VGG19_config import cfg as network_cfg
    from user_config import cfg as dataset_cfg
    return merge_configs([detector_cfg, network_cfg, dataset_cfg])
def get_configuration_alexnet():
    # load configs for detector, base network and data set
    from utils.configs.FasterRCNN_config import cfg as detector_cfg
    from utils.configs.AlexNet_config import cfg as network_cfg
    from user_config import cfg as dataset_cfg
    return merge_configs([detector_cfg, network_cfg, dataset_cfg])

def prepare_detect(cfg, use_arg_parser=True):
    cfg.MB_SIZE = 1
    cfg.NUM_CHANNELS = 3
    np.random.seed(seed=cfg.RND_SEED)

def imreadEX(image_path):
    if re.compile('[^ ㄱ-ㅣ가-힣]+').sub('', image_path):
        stream = open(image_path, "rb")
        bytes = bytearray(stream.read())
        numpyarray = np.asarray(bytes, dtype=np.uint8)
        img = cv2.imdecode(numpyarray, cv2.IMREAD_UNCHANGED)
    else:
        img = cv2.imread(image_path)
    return img

STANDARD_RIGHTS_REQUIRED = 0x000F0000
SYNCHRONIZE = 0x00100000
MUTANT_QUERY_STATE = 0x0001
MUTEX_ALL_ACCESS = STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | MUTANT_QUERY_STATE

if(len(sys.argv)<5):
    print("Usage : ")
    print("arguments : [base model(AlexNet,VGG16,VGG19)] [WEIGHTS file path] [IMAGE file path] [THRESHOLD]")
    print("example : FasterRCNN_Test_SE AlexNet faster_rcnn_eval_AlexNet_e2e.model 0001.jpg 0.9")
    sys.exit(1)

MODEL=sys.argv[1]
WEIGHTS=sys.argv[2]
IMAGE=sys.argv[3]
THRESHOLD=float(sys.argv[4])
if(MODEL=="VGG16"):
    cfg = get_configuration_vgg16()
if(MODEL=="VGG19"):
    cfg = get_configuration_vgg19()
if(MODEL=="AlexNet"):
    cfg = get_configuration_alexnet()
prepare_detect(cfg, False)

model=load_model(WEIGHTS)


# make evaluator
evaluator = FasterRCNN_Evaluator(model, cfg)
# prepare main image detect. BCZ It is too slow first,second time.
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
# model load finished


regressed_rois, cls_probs = od.predict_single_image(model, IMAGE, cfg, evaluator)
cfg.RESULTS_NMS_THRESHOLD=0.5
cfg.RESULTS_NMS_CONF_THRESHOLD=THRESHOLD
cfg.USE_GPU_NMS=False
bboxes, labels, scores = od.filter_results(regressed_rois, cls_probs, cfg)

img = imreadEX(IMAGE)
height, width = img.shape[:2]
scale = 850.0 / max(width, height)
pad = int((max(height, width) - min(height, width)) / 2)

for i in range(0, len(bboxes)):
    if(labels[i]!=0 and scores[i]>=THRESHOLD):
        bboxes[i] /= scale
        if (width > height):
            bboxes[i][1] -= pad
            bboxes[i][3] -= pad
        else:
            bboxes[i][0] -= pad
            bboxes[i][2] -= pad
        cv2.putText(img, "class"+str(labels[i])+"("+str(scores[i])+")", (bboxes[i][0],bboxes[i][1]), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0,0,255), 2)
        cv2.rectangle(img, (bboxes[i][0],bboxes[i][1]),(bboxes[i][2],bboxes[i][3]),(0,0,255),2)

cv2.imshow('result',img)
cv2.waitKey()

#http://blog.csdn.net/yatere/article/details/7237023
#https://mail.python.org/pipermail/python-list/2005-April/311564.html
#https://stackoverflow.com/questions/15526665/wait-until-a-mutex-is-created-in-python-win32
#https://stackoverflow.com/questions/26114518/ipc-between-python-and-win32-on-windows-os
#=====EXE=====
#http://infocentre.tistory.com/3
