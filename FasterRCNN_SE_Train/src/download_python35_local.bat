::python3.5.3 local packace.
::See also https://github.com/springkim/FasterRCNN_SpringEdition
powershell "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;(New-Object System.Net.WebClient).DownloadFile('https://github.com/springkim/FasterRCNN_SpringEdition/releases/download/cntk/Python35.zip','Python35.zip')"
powershell.exe -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('Python35.zip', '.'); }"
IF EXIST "Python35.zip" (
	DEL "Python35.zip"
)
