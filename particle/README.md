插件示例，使用cmake进行编译。

## 编译

* mac/linux/windows

    ```
    $ mkdir -p build/native
    $ cd build/native
    $ cmake ../../
    $ cmake --build .
    ```

    mac 上再执行一次 ``make install`` ，会设置好动态库的rpath。

* android

    ```
    $ mkdir -p build/android/armeabi
    $ cd build/android/armeabi
    $ cmake ../../../ \
    	-DCMAKE_TOOLCHAIN_FILE=../../../engine_export/cmake/android.cmake \
    	-DCMAKE_BUILD_TYPE=Release \
    	-DANDROID_ABI=armeabi \
    	-DANDROID_STL=gnustl_static \
    	-DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9
    $ cmake --build .
    ```

    `ANDROID_ABI` 可取值： armeabi/armeabi-v7a/x86/mips/armeabi-v7a with NEON/armeabi-v7a with VFPV3/armeabi-v6 with VFP/arm64-v8a/x86_64/mips64

* ios

    ```
    $ mkdir -p build/ios
    $ cd build/ios
    $ cmake ../../ \
        -DCMAKE_TOOLCHAIN_FILE=../../engine_export/cmake/ios.cmake \
        -DIOS_PLATFORM=OS \
        -DCMAKE_BUILD_TYPE=Release \
        -GXcode
    $ cmake --build .
    ```

    编模拟器版本，可指定 `IOS_PLATFORM` 为 SIMULATOR 或 SIMULATOR64 。
