powershell "(New-Object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/9gox6h7a846ydpq/bin.zip?dl=1','%TEMP%\bin.zip')"
powershell -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('%TEMP%\bin.zip', '.'); }"
IF EXIST "%TEMP%\bin.zip" (
	DEL "%TEMP%\bin.zip"
)
