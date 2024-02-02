插件示例，使用 python 进行编译。

- 需要安装的环境

  `python 2.7.15`

  `Visual Studio 2015`

  `NDKr21b`

  `cmake-3.13.3`

- mac/linux/windows

  \*生成 makefile&&编译

  ```shell
  $ python BuildPlugin.py -p native
  ```

  \*仅编译

  ```shell
  $ python BuildPlugin.py -p native -buildOnly y
  ```

  \*编译 debug 默认 release

  ```shell
  $ python BuildPlugin.py -p native -d y
  ```

- ios

  \*生成 makefile&&编译

  ```shell
  $ python BuildPlugin.py -p ios
  ```

  \*仅编译

  ```shell
  $ python BuildPlugin.py -p ios -buildOnly y
  ```

- android

  \*生成 makefile&&编译

  \*生成所有

  ```shell
  $ python BuildPlugin.py -p android
  ```

  \*生成指定`abi`

  ```shell
  $ python BuildPlugin.py -p android -t armeabi-v7a
  ```

  \*仅编译指定`abi`

  ```shell
  $ python BuildPlugin.py -p android -t armeabi-v7a -buildOnly y
  ```

  \*仅编译所有

  ```shell
  $ python BuildPlugin.py -p android -buildOnly y
  ```

插件示例，使用 cmake 进行编译。

## 编译

- mac/linux/windows

  ```
  $ mkdir -p build/native
  $ cd build/native
  $ cmake -G "Visual Studio 14" ../../
  $ cmake --build .
  ```

  mac 上再执行一次 `make install` ，会设置好动态库的 rpath。

- android

  ```
  $ mkdir -p build/android/armeabi-v7a
  $ cd build/android/armeabi-v7a
  $ cmake ../../../ \
    -DCMAKE_TOOLCHAIN_FILE=../../../engine_export/cmake/android.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_ABI=armeabi-v7a \
    -DANDROID_STL=c++_static
  $ cmake --build .
  ```

  ```
  $ mkdir -p build/android/armeabi-v7a
  $ cd build/android/armeabi-v7a
  $ cmake ../../../ \
      -DCMAKE_TOOLCHAIN_FILE=../../../engine_export/cmake/android.cmake \
      -DCMAKE_BUILD_TYPE=Release \
      -DANDROID_ABI=armeabi-v7a \
      -DANDROID_STL=c++_static`
  $ cmake --build .
  ```

    <!-- `ANDROID_ABI` 可取值： armeabi/armeabi-v7a/x86/mips/armeabi-v7a with NEON/armeabi-v7a with VFPV3/armeabi-v6 with VFP/arm64-v8a/x86_64/mips64 -->

- ios

  ```
  $ mkdir -p build/ios
  $ cd build/ios
  $ cmake ../../../ \
      -DCMAKE_TOOLCHAIN_FILE=../../../engine_export/cmake/ios.cmake \
      -DIOS_PLATFORM=OS \
      -DCMAKE_BUILD_TYPE=Release \
      -GXcode
  $ cmake --build .
  ```

  编模拟器版本，可指定 `IOS_PLATFORM` 为 SIMULATOR 或 SIMULATOR64 。
## 上传

- ios
  \*首次的时候需要添加git
  ```shell
  $ sh AddGit.sh
  ```

  ```shell
  $ python copyRemote.py -p ios -v 0.0.1
  ```

- android

  ```shell
  $ python copyRemote.py -p android -v 0.0.1
  ```