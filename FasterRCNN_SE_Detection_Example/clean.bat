call :SafeDEL "*.dll"
call :SafeDEL "*.exe"
call :SafeDEL "*.model"
call :SafeDEL "class_map.txt"
call :SafeDEL "result.jpg"
call :SafeDEL "*.iobj"
call :SafeDEL "*.ipdb"
call :SafeDEL "*.ilk"
call :SafeDEL "*.pdb"

call :SafeRMDIR "x64"

:SafeDEL
IF EXIST %~1 (
	DEL %~1
)
exit /b

:SafeRMDIR
IF EXIST %~1 (
	RMDIR /S /Q %~1
)
exit /b