powershell "(New-Object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/s3xel6z1e09s9cp/3rdparty.zip?dl=1','%TEMP%\3rdparty.zip')"
powershell -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('%TEMP%\3rdparty.zip', '.'); }"
IF EXIST "%TEMP%\3rdparty.zip" (
	DEL "%TEMP%\3rdparty.zip"
)
