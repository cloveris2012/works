@echo off
echo %cd%
set cur=%cd%
set build=%cur%\build
set Release=%build%\native\win32\RelWithDebInfo
set dll=%build%\native\win32\RelWithDebInfo\pb3.dll
set target=V:\��ʱ����"("����3��")"\IDE\plugins\pb3\win32\
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

