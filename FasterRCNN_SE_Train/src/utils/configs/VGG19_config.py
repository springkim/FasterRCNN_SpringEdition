# Copyright (c) Microsoft. All rights reserved.

# Licensed under the MIT license. See LICENSE.md file in the project root
# for full license information.
# ==============================================================================

# `pip install easydict` if you don't have it
from easydict import EasyDict as edict

__C = edict()
__C.MODEL = edict()
cfg = __C

# model config
__C.MODEL.BASE_MODEL = "VGG19"
__C.MODEL.BASE_MODEL_FILE = "VGG19_ImageNet_Caffe.model"
__C.MODEL.IMG_PAD_COLOR = [103, 116, 123]
__C.MODEL.FEATURE_NODE_NAME = "data"
__C.MODEL.LAST_CONV_NODE_NAME = "relu5_4"
__C.MODEL.START_TRAIN_CONV_NODE_NAME = "pool2" # __C.MODEL.FEATURE_NODE_NAME
__C.MODEL.POOL_NODE_NAME = "pool5"
__C.MODEL.LAST_HIDDEN_NODE_NAME = "drop7"
__C.MODEL.FEATURE_STRIDE = 16
__C.MODEL.RPN_NUM_CHANNELS = 512
__C.MODEL.ROI_DIM = 7
__C.MODEL.E2E_LR_FACTOR = 1.0
__C.MODEL.RPN_LR_FACTOR = 1.0
__C.MODEL.FRCN_LR_FACTOR = 1.0
