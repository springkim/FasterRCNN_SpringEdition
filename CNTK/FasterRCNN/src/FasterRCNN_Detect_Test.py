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

def get_configuration():
    from utils.configs.FasterRCNN_config import cfg as detector_cfg
    from utils.configs.VGG16_config import cfg as network_cfg
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

cfg=get_configuration()
prepare_detect(cfg, False)

model=load_model('../faster_rcnn_eval_VGG16_e2e.model')
# make evaluator
evaluator = FasterRCNN_Evaluator(model, cfg)
# prepare main image detect. BCZ It is too slow first,second time.
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
# model load finished


img_path = '../이미지/0000.jpg'

regressed_rois, cls_probs = od.predict_single_image(model, img_path, cfg, evaluator)

img = imreadEX(img_path)
height, width = img.shape[:2]
scale = 850.0 / max(width, height)
pad = int((max(height, width) - min(height, width)) / 2)

for i in range(0, len(regressed_rois)):
    m_class=0
    m_score=0
    for j in range(0,len(cls_probs[i])):
        if(m_score<cls_probs[i][j]):
            m_score=cls_probs[i][j]
            m_class=j
    if(m_class!=0 and cls_probs[i][m_class]>0.4):
        regressed_rois[i] /= scale
        if (width > height):
            regressed_rois[i][1] -= pad
            regressed_rois[i][3] -= pad
        else:
            regressed_rois[i][0] -= pad
            regressed_rois[i][2] -= pad
        cv2.rectangle(img, (regressed_rois[i][0],regressed_rois[i][1]),(regressed_rois[i][2],regressed_rois[i][3]),(0,0,255))

cv2.imshow('result',img)
cv2.waitKey()

#http://blog.csdn.net/yatere/article/details/7237023
#https://mail.python.org/pipermail/python-list/2005-April/311564.html
#https://stackoverflow.com/questions/15526665/wait-until-a-mutex-is-created-in-python-win32
#https://stackoverflow.com/questions/26114518/ipc-between-python-and-win32-on-windows-os
#=====EXE=====
#http://infocentre.tistory.com/3