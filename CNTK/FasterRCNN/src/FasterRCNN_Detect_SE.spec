# -*- mode: python -*-

block_cipher = None


a = Analysis(['FasterRCNN_Detect_SE.py'],
             pathex=['C:\\Users\\spring\\Documents\\SourceTree\\FasterRCNN_SpringEdition\\CNTK\\FasterRCNN\\src'],
             binaries=[],
             datas=[],
             hiddenimports=['utils.rpn.proposal_layer'],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          name='FasterRCNN_Detect_SE',
          debug=False,
          strip=False,
          upx=True,
          runtime_tmpdir=None,
          console=True , icon='leaf.ico')
