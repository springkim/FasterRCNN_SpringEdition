powershell "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;(New-Object System.Net.WebClient).DownloadFile('https://github.com/springkim/FasterRCNN_SpringEdition/releases/download/cntk/bin.zip','%TEMP%\bin.zip')"
powershell -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('%TEMP%\bin.zip', '.'); }"
IF EXIST "%TEMP%\bin.zip" (
	DEL "%TEMP%\bin.zip"
)
