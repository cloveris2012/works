@REM @Author: LensarZhang
@REM @Date:   2020-04-09 14:26:13
@REM @Last Modified by:   LensarZhang
@REM Modified time: 2021-02-23 09:52:21

if NOT exist build (
mkdir build
)

cd build

if NOT exist arm64-v8a (
mkdir arm64-v8a
)

cd arm64-v8a

cmake -GNinja ../../ -DANDROID_ABI=arm64-v8a -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_MAKE_PROGRAM=C:\\ninja -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%\\build\\cmake\\android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_TOOLCHAIN=clang -DANDROID_NATIVE_API_LEVEL=21
cmake --build . --config Release

cd ..

if NOT exist armeabi-v7a (
mkdir armeabi-v7a
)

cd armeabi-v7a

cmake -GNinja ../../ -DANDROID_ABI=armeabi-v7a -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_MAKE_PROGRAM=C:\\ninja -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%\\build\\cmake\\android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_TOOLCHAIN=clang -DANDROID_NATIVE_API_LEVEL=21
cmake --build . --config Release

cd ..

if NOT exist x86 (
mkdir x86
)

cd x86

cmake -GNinja ../../ -DANDROID_ABI=x86 -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_MAKE_PROGRAM=C:\\ninja -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%\\build\\cmake\\android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_TOOLCHAIN=clang -DANDROID_NATIVE_API_LEVEL=21
cmake --build . --config Release

cd ..

if NOT exist x86_64 (
mkdir x86_64
)

cd x86_64

cmake -GNinja ../../ -DANDROID_ABI=x86_64 -DANDROID_NDK=%ANDROID_NDK% -DCMAKE_MAKE_PROGRAM=C:\\ninja -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%\\build\\cmake\\android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_TOOLCHAIN=clang -DANDROID_NATIVE_API_LEVEL=21
cmake --build . --config Release
