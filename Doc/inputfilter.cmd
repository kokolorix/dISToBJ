@echo off

cd /d "%~dp0"

REM echo %* >> inputfilter.log

set file=%~1
set file=%file:/=\%
echo %file% >> inputfilter.log
type "%file%"
