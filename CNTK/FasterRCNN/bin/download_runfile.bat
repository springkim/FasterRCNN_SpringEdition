::Train file
powershell "(New-Object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/p726xk5pjvzxvly/FasterRCNN_Train_SE.exe?dl=1','FasterRCNN_Train_SE.exe')"

::Download requirement dlls
powershell "(New-Object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/tj0c19eoz17yzgo/FasterRCNN_SE_dll.zip?dl=1','FasterRCNN_SE_dll.zip')"

powershell.exe -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('FasterRCNN_SE_dll.zip', '.'); }"

IF EXIST "FasterRCNN_SE_dll.zip" (
	DEL "FasterRCNN_SE_dll.zip"
)