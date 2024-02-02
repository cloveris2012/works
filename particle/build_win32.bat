@echo off
echo %cd%
set cur=%cd%
set build=%cur%\build
set Release=%build%\native\win32\RelWithDebInfo
set dll=%build%\native\win32\RelWithDebInfo\particle.dll
set target=V:\临时共享"("保留3天")"\IDE\plugins\particle\win32\
del /S /Q %build%
if exist %dll% (
	del /S /Q %dll%
)

python BuildPlugin.py -p native

if not exist %dll% (
	echo "build failed"
	exit 1
)

symuploader upload -src %Release% -emails YuchengMo@boyaa.com,HengLi@boyaa.com
net use V: \\boyaa.com\byDFS

xcopy %dll% %target% /s /e /y

echo -----------

