from utils.FasterRCNN_train import train_faster_rcnn,store_eval_model_with_native_udf
from utils.config_helpers import merge_configs
from utils.annotations.annotations_helper import parse_class_map_file
import os
import sys
import numpy as np
def count(filename):
    lines = 0
    for line in open(filename):
        lines += 1
    return lines

def get_configuration(EPOCH):
    # load configs for detector, base network and data set
    from utils.configs.FasterRCNN_config import cfg as detector_cfg
    from utils.configs.VGG16_config import cfg as network_cfg
    from user_config import cfg as dataset_cfg
    detector_cfg["CNTK"].E2E_MAX_EPOCHS=EPOCH
    dataset_cfg["DATA"].NUM_TRAIN_IMAGES=count("../"+dataset_cfg["DATA"].TRAIN_MAP_FILE)
    return merge_configs([detector_cfg, network_cfg, dataset_cfg])
def prepare_train(cfg, use_arg_parser=True):
    cfg.MB_SIZE = 1
    cfg.NUM_CHANNELS = 3
    cfg.OUTPUT_PATH = "../"
    cfg["DATA"].MAP_FILE_PATH = "../"

    data_path = cfg["DATA"].MAP_FILE_PATH
    if not os.path.isdir(data_path):
        raise RuntimeError("Directory %s does not exist" % data_path)

    cfg["DATA"].CLASS_MAP_FILE = os.path.join(data_path, cfg["DATA"].CLASS_MAP_FILE)
    cfg["DATA"].TRAIN_MAP_FILE = os.path.join(data_path, cfg["DATA"].TRAIN_MAP_FILE)
    #cfg["DATA"].TEST_MAP_FILE = os.path.join(data_path, cfg["DATA"].TEST_MAP_FILE)
    cfg["DATA"].TRAIN_ROI_FILE = os.path.join(data_path, cfg["DATA"].TRAIN_ROI_FILE)
    #cfg["DATA"].TEST_ROI_FILE = os.path.join(data_path, cfg["DATA"].TEST_ROI_FILE)

    cfg['MODEL_PATH'] = os.path.join(cfg.OUTPUT_PATH, "faster_rcnn_eval_{}_{}.model"
                                     .format(cfg["MODEL"].BASE_MODEL, "e2e" if cfg["CNTK"].TRAIN_E2E else "4stage"))
    cfg['BASE_MODEL_PATH'] = "../VGG16_ImageNet_Caffe.model"

    cfg["DATA"].CLASSES = parse_class_map_file(cfg["DATA"].CLASS_MAP_FILE)
    cfg["DATA"].NUM_CLASSES = len(cfg["DATA"].CLASSES)

    if cfg["CNTK"].FAST_MODE:
        cfg["CNTK"].E2E_MAX_EPOCHS = 1
        cfg["CNTK"].RPN_EPOCHS = 1
        cfg["CNTK"].FRCN_EPOCHS = 1

    np.random.seed(seed=cfg.RND_SEED)


EPOCH=int(sys.argv[1])

cfg = get_configuration(EPOCH)
prepare_train(cfg, False)
model = train_faster_rcnn(cfg)

#store_eval_model_with_native_udf(model, cfg)