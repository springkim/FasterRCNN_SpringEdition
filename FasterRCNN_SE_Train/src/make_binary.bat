set path=%path%;%cd%\Python35;%cd%\Python35\Scripts
python35 Python35\Scripts\pyinstaller-script.py FasterRCNN_Train_SE.py -F --hidden-import=utils.rpn.proposal_layer --icon=leaf.ico
python35 Python35\Scripts\pyinstaller-script.py FasterRCNN_Detect_SE.py -F --hidden-import=utils.rpn.proposal_layer --icon=leaf.ico
python35 Python35\Scripts\pyinstaller-script.py FasterRCNN_Test_SE.py -F --hidden-import=utils.rpn.proposal_layer --icon=leaf.ico
move /Y %cd%\dist\*.exe %cd%\
rmdir /S /Q build
rmdir /S /Q dist
