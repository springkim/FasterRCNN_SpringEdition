::python3.5.3 local packace.
::See also https://github.com/springkim/FasterRCNN_SpringEdition
powershell "(New-Object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/o7p3byhb7j8nvsf/Python35.zip?dl=1','Python35.zip')"
powershell.exe -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('Python35.zip', '.'); }"
IF EXIST "Python35.zip" (
	DEL "Python35.zip"
)
