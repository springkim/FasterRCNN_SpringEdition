powershell "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;(New-Object System.Net.WebClient).DownloadFile('https://github.com/springkim/FasterRCNN_SpringEdition/releases/download/bin/3rdparty.zip','%TEMP%\3rdparty.zip')"
powershell -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('%TEMP%\3rdparty.zip', '.'); }"
IF EXIST "%TEMP%\3rdparty.zip" (
	DEL "%TEMP%\3rdparty.zip"
)
pause