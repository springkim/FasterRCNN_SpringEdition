pyinstaller FasterRCNN_Train_SE.py -F --hidden-import=utils.rpn.proposal_layer --icon=leaf.ico
pyinstaller FasterRCNN_Detect_SE.py -F --hidden-import=utils.rpn.proposal_layer --icon=leaf.ico