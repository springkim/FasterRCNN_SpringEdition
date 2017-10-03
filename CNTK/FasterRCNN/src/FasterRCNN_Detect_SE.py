import os
import sys
import time
import numpy as np
import cv2
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
STANDARD_RIGHTS_REQUIRED = 0x000F0000
SYNCHRONIZE = 0x00100000
MUTANT_QUERY_STATE = 0x0001
MUTEX_ALL_ACCESS = STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | MUTANT_QUERY_STATE
#
#   argv[1]=shmem key
#   argv[2]=mutex key
#   argv[3]=model path
#
shmem_key=sys.argv[1]
mutex_key=sys.argv[2]
shmem_size=int(sys.argv[3])
model_path=sys.argv[4]
shm = mmap.mmap(0,shmem_size,shmem_key)
mutex = win32event.OpenMutex(MUTEX_ALL_ACCESS, False, mutex_key)
if not (mutex):
    print("mutex fail")
    sys.exit(1)
if not(shm):
    print("shmem fail")
    sys.exit(1)
cfg=get_configuration()
prepare_detect(cfg, False)

model=load_model(model_path)
# make evaluator
evaluator = FasterRCNN_Evaluator(model, cfg)
# prepare main image detect. BCZ It is too slow first,second time.
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
od.predict_dummy_image(model,  cfg,evaluator)
# model load finished
win32event.WaitForSingleObject(mutex,win32event.INFINITE)
shm.write(bytes(str(1), "ascii"))
win32event.ReleaseMutex(mutex)
#=======================================================================================================================
while(True):
    win32event.WaitForSingleObject(mutex,win32event.INFINITE)
    shm.seek(0)
    run_type = shm.read(1)
    if(run_type == b'2'):
        img_path = str(shm.read(256),"ascii")
        #detect
        regressed_rois, cls_probs = od.predict_single_image(model, img_path, cfg, evaluator)
        #fix roi
        img = cv2.imread(img_path)
        height, width = img.shape[:2]
        scale = 850.0 / max(width, height)
        pad = int((max(height, width) - min(height, width)) / 2)
        passdata=""
        num=0
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
                passdata+=str(m_class)+";"+str(int(m_score*10000))+";"+str(int(regressed_rois[i][0]))+";"+str(int(regressed_rois[i][1]))+";"+str(int(regressed_rois[i][2]))+";"+str(int(regressed_rois[i][3]))+";"
                num+=1
        passdata=str(num)+";"+passdata
        shm.seek(0)
        shm.write(bytes(str(3),"ascii"))
        shm.write(bytes(passdata,"ascii"))
    if(run_type == b'9'):
        win32event.ReleaseMutex(mutex)
        break
    win32event.ReleaseMutex(mutex)
#=====IPC=====
#http://blog.csdn.net/yatere/article/details/7237023
#https://mail.python.org/pipermail/python-list/2005-April/311564.html
#https://stackoverflow.com/questions/15526665/wait-until-a-mutex-is-created-in-python-win32
#https://stackoverflow.com/questions/26114518/ipc-between-python-and-win32-on-windows-os
#=====EXE=====
#http://infocentre.tistory.com/3