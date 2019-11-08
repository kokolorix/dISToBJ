@echo off
call :%*
exit /b %errorlevel%

:saveTime <resultVariable>
if "%Time:~0,1%"==" " (set %~1=0%Time:~1,7%) else (set %~1=%Time:~0,8%)
exit /b 0

:calcDuration <startTime> <endTime> <result>
setlocal
set n1=%~1
:: call ist wichtig damit die Variable aufgelöst wird
call set st=%%%n1%%%
set n2=%~2
call set et=%%%n2%%%
echo Start:    %st%
echo End:      %et%
set /A "ss=(((1%et::=-100)*60+1%-100)-(((1%st::=-100)*60+1%-100)"
set /A "hh=ss/3600+100,ss%%=3600,mm=ss/60+100,ss=ss%%60+100"
echo Dauer:    %hh:~1%:%mm:~1%:%ss:~1%
:: exportiert die übergebene Variable %~3 damit der Wert beim Aufrufer  ankommt
endlocal && set %~3=%hh:~1%:%mm:~1%:%ss:~1%
exit /b 0

:save4Letters <resultVariable>
set tmp=%cd:~-4%
set tmp=%tmp:\=%
set %~1=%tmp%
set tmp=
exit /b 0

:prepareTest <mandantDir> <shareRoot>
set pgm=%cd%\Pgm
echo Programmordner: %pgm%

pushd %~1
endlocal
call :save4Letters mandant
echo Mandant: %mandant%
popd

call :evalShare share %~2
echo Datenordner: %share%


:regProtocol <protocol> <icon> <command>
if %reg_prot%==N exit /b 0
setlocal

net session >nul 2>&1
if %errorLevel% == 0 (
	echo Yes: Administrative permissions confirmed.
	goto:writeRegProtocol
) else (
	echo No: Current permissions inadequate. Try to upgrade them.
	pushd "%~dp0"
	sudo cmd /c call "%~dp0\Helpers" writeRegProtocol %*
	popd
	exit /b 0	
)

:writeRegProtocol <protocol> <icon> <command>
set protocol=%~1
set icon=%~2
set command=%~3

echo Registriere Protokoll %protocol% ... %*

call reg add HKCR\%protocol% /ve /t REG_SZ /d "URL:ElektroForm15" /f>nul
call reg add HKCR\%protocol% /v "URL Protocol" /t REG_SZ /f>nul
call reg add HKCR\%protocol%\defaulticon /ve /t REG_SZ /d "%icon%" /f>nul
call reg add HKCR\%protocol%\shell /ve /t REG_SZ /d "open" /f>nul
call reg add HKCR\%protocol%\shell\open\command /ve /t REG_SZ /d "%command% \"%%%%1\"" /f>nul
exit /b 0


:createLnk <ProgramName> <WorkingDirectory> <Arguments> <Description> <Icon> <AsAdmin>
setlocal
REM cd /d "%~dp0"
REM echo %*
REM echo ProgramName: %1 WorkingDirectory: %2 Arguments: %3 Description: %4 Icon: %5 AsAdmin: %6
if "%~2"=="" (set lnk=%cd%\%~4.lnk) else (set lnk=%cd%\%~n1%~4.lnk)
REM echo Erstelle %lnk%

if "%~2"=="" (
	if "%~dp1"=="" (set wcd=%cd%) else (set wcd=%~dp1)	
) else (
	set wcd=%~2
)
REM echo wcd: %wcd%

REM echo ~x1=%~x1
if "%~x1"=="" (
	REM echo ~dp1=%~dp1
	if "%~dp1"=="" (
		set trg=%wcd%\%~1.exe
	) else (
		set trg=%~1.exe
	)	
) else (
	REM echo ~dp1=%~dp1
	if '%~dp1'=='' (
		set trg=%wcd%\%~1
	) else (
		set trg=%~1
	)	
)
REM echo trg: %trg%

set arg="%~3"
set dsc=%4
if "%~5"=="" (set ico=%trg%) else (set ico=%~5)

pushd "%~dp0"
echo $ws =  New-Object -comObject WScript.Shell > create-shortcut.ps1
echo $lnk = $ws.CreateShortcut("%lnk%") >> create-shortcut.ps1
echo $lnk.TargetPath = "%trg%" >> create-shortcut.ps1
echo $lnk.WorkingDirectory = "%wcd%" >> create-shortcut.ps1
echo $lnk.Arguments = %arg% >> create-shortcut.ps1
REM echo $lnk.Description = "My Application" >> create-shortcut.vbs
echo $lnk.IconLocation = "%ico%" >> create-shortcut.ps1
echo $lnk.Save() >> create-shortcut.ps1

if "%~6"=="" goto:write_lnk

:admin_lnk
REM echo Als Administrator (%~6)
echo $bytes = [System.IO.File]::ReadAllBytes("%lnk%") >> create-shortcut.ps1
:: #set byte 21 (0x15) bit 6 (0x20) ON 
echo $bytes[0x15] = $bytes[0x15] -bor 0x20 >> create-shortcut.ps1
echo [System.IO.File]::WriteAllBytes("%lnk%", $bytes) >> create-shortcut.ps1

:write_lnk
call powershell -File create-shortcut.ps1
REM pause
erase create-shortcut.ps1
popd
exit /b 0

:recycleIt
setlocal
REM if exist %1 echo Recycle %~1
if exist %1 call powershell -Command "Add-Type -AssemblyName Microsoft.VisualBasic;[Microsoft.VisualBasic.FileIO.FileSystem]::DeleteFile('%~1','OnlyErrorDialogs','SendToRecycleBin')"
title %~n0 - %~dp0
exit /b 0

:linkIt
setlocal
REM echo %1
call :recycleIt %1
call mklink /H %1 %2
exit /b 0

:evalShare <resultShare> <shareRoot>
pushd %~2
if exist %cd% call :strlen len %cd%
popd
setlocal EnableDelayedExpansion
set rel=!cd:~%len%!
endlocal && set %~1=\\%COMPUTERNAME%\Test%rel%

setlocal EnableDelayedExpansion
if not exist !%~1! (
	endlocal && set %~1=%~dp0
	exit /b 0
)
exit /b 0

:set <in> <out>
set %~2=%~1
exit /b 0 


:strlen <resultVar> <stringVar>
echo %~2>_strlen_
for %%? in (_strlen_) do set /A %~1=%%~z? - 2
del _strlen_
exit /b 0


echo sollte nie erreicht werden
exit /b -1