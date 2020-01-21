@echo off

cd /d "%~dp0"

pushd ..
set PATH=%cd%\Tools;%PATH%
popd

if "%~1"=="" (
    call "%~0" "XxX" | mtee dISToBJ.dox.log
    exit /b 0
)

call helpers saveTime startTime
echo Start:     %startTime%

if exist inputfilter.log call erase inputfilter.log
call doxygen dISToBJ.dox -d extcmd

call helpers saveTime endTime
call helpers calcDuration startTime endTime duration

goto:wait

:wait
set wait=2
choice /c wq /t %wait% /d q /m "W=pause, Q=quit(%wait%s)"
if errorlevel 2 goto:eof
if errorlevel 1 goto:exit

:exit
pause


