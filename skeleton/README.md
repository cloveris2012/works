# skeleton

## 编译
* mac/linux/windows
* android
* ios
```
cmake ../../ \
    -DCMAKE_TOOLCHAIN_FILE=../../engine_export/cmake/ios.cmake \
    -DIOS_PLATFORM=OS \
    -DCMAKE_BUILD_TYPE=Release \
    -GXcode
$ cmake --build .
```