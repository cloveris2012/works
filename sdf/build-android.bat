if NOT exist build (
mkdir build
)

cd build

if NOT exist android (
mkdir android
)

cd android

if NOT exist arm64-v8a (
mkdir arm64-v8a
)

cd arm64-v8a

cmake ../../../ -G"Ninja" -DANDROID_ABI=arm64-v8a -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="C:\ninja.exe" -DCMAKE_TOOLCHAIN_FILE="%ANDROID_NDK%/build/cmake/android.toolchain.cmake" -DANDROID_PLATFORM=21 -DANDROID_TOOLCHAIN=clang
cmake --build .

cd ..

if NOT exist armeabi-v7a (
mkdir armeabi-v7a
)
 
cd armeabi-v7a

cmake ../../../ -G"Ninja" -DANDROID_ABI=armeabi-v7a -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="C:\ninja.exe" -DCMAKE_TOOLCHAIN_FILE="%ANDROID_NDK%/build/cmake/android.toolchain.cmake" -DANDROID_PLATFORM=21 -DANDROID_TOOLCHAIN=clang
cmake --build .

cd ..

if NOT exist x86 (
mkdir x86
)

cd x86

cmake ../../../ -G"Ninja" -DANDROID_ABI=x86 -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="C:\ninja.exe" -DCMAKE_TOOLCHAIN_FILE="%ANDROID_NDK%/build/cmake/android.toolchain.cmake" -DANDROID_PLATFORM=21 -DANDROID_TOOLCHAIN=clang
cmake --build .

cd ..

if NOT exist x86_64 (
mkdir x86_64
)

cd x86_64

cmake ../../../ -G"Ninja" -DANDROID_ABI=x86_64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="C:\ninja.exe" -DCMAKE_TOOLCHAIN_FILE="%ANDROID_NDK%/build/cmake/android.toolchain.cmake" -DANDROID_PLATFORM=21 -DANDROID_TOOLCHAIN=clang
cmake --build .