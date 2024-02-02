#!/usr/bin/env python
# coding: utf-8
import os, sys
import os.path
import argparse

def build_parser():
    parser = argparse.ArgumentParser()
    # parser.add_argument('-e', '--event',required=True,help='1:camake generate,2:camake build')
    parser.add_argument('-p', '--platform',required=True, help='platform name like ios android win')
    parser.add_argument('-t', '--abi', help='abi order string')
    parser.add_argument('-d','--debug', help='build debug')
    parser.add_argument('-buildOnly', '--buildOnly', help='only build project')
    args = parser.parse_args()

    return args

def createAndroid(abi_android):
    build_type = "Release"
    # print("createAndroid____________")
    if is_debug:
        build_type = "Debug"
    os.system('''cd build/android/{abi};cmake ../../../ \
                          -DCMAKE_TOOLCHAIN_FILE=../../../engine_export/cmake/android.cmake \
                          -DCMAKE_BUILD_TYPE={bt} \
                          -DANDROID_ABI={abi} \
                          -DANDROID_STL=c++_static'''.format(bt = build_type,abi=abi_android))
def createIos(ios_platform):
    # print("createIos_____________")
    build_type = "Release"
    if is_debug:
        build_type = "Debug"
    os.system('''cd build/ios/{platform};cmake ../../../ \
                    -DCMAKE_TOOLCHAIN_FILE=../../../engine_export/cmake/ios.cmake \
                    -DIOS_PLATFORM={platform} \
                    -DCMAKE_BUILD_TYPE={bt} \
                    -GXcode'''.format(platform = ios_platform,bt = build_type))

def generateAllIos():
    for platform in ios_platforms:
        createIos(platform)

def createNative():
    if sys.platform == "win32":
        os.chdir("build/native/win32")
        print(is_debug)
        # os.system('''cmake -DCMAKE_BUILD_TYPE=Release''')
        os.system('''cmake -G "Visual Studio 14" ../../../ \
                                ''')
    else:
        print(is_debug)
        # os.system('''cmake -DCMAKE_BUILD_TYPE=Release''')
        os.system('''cd build/native/mac;cmake ../../../;make install''')

def generateAllAndroid():
    for abi in android_abis:
        createAndroid(abi)

def generateProject(args):
    if platform == "ios":
        if not args.abi:
            generateAllIos()
        else:
            createIos(args.abi)
    elif platform == "android":
        if not args.abi:
            generateAllAndroid()
        else:
            createAndroid(args.abi)
    else:
        createNative()

def getLibName():
    file_dir_path = "build/ios/OS/Release-iphoneos"
    file_name = ''
    for root, dirs, files in os.walk(file_dir_path):
        file_name = files[0]

    return file_name

def installIos():
    file_name = getLibName()
    os.system('''lipo -output build/ios/{lib_name} \
                        -create build/ios/OS/Release-iphoneos/{lib_name} \
                        '''.format(lib_name=file_name))

def buildProject(args):
    # print("buildProject")
    if platform == "ios":
        os.system('''cd build/ios;cmake --build .''')
        if args.abi == None:
            for abi in ios_platforms:
                os.system('''cd build/ios/{abi};cmake --build . --config Release'''.format(abi=abi))
        else:
            os.system('''cd build/ios/{abi};cmake --build . --config Release'''.format(abi=args.abi))
        installIos()
    elif platform == "android":
        if args.abi == None:
            for abi_android in android_abis:
                os.system('''cd build/android/{abi};cmake --build . --config Release'''.format(abi=abi_android))
                # os.system('''cd build/android/{abi};cmake --build .'''.format(abi=abi_android))
                # os.system('''cd build/android/{abi};cmake --build .'''.format(abi=abi_android))
        else:
            os.system('''cd build/android/{abi};cmake --build . --config Release'''.format(abi=args.abi))
    elif platform == "native":
        # os.chdir("build/native")
        if sys.platform == "win32":
            if is_debug:
                os.system('''cmake  --build . --config Debug''')
            
            os.system('''cmake  --build . --config RelWithDebInfo''')

        else:
            if is_debug:
                os.system('''cd build/native/mac;cmake  --build . --config Debug''')
            os.system('''cd build/native/mac;cmake  --build . --config Release''')
#创建文件夹
def createDir(build_dir,abi):
    path_str = "{platform}/{abi}".format(platform=platform, abi=abi)
    platform_dir = os.path.join(build_dir, path_str)
    if not os.path.exists(platform_dir):
        os.makedirs(platform_dir)
#创建平台build/platform文件夹
def makeDir(args):
    # 项目跟目录
    root_dir = sys.path[0]
    # build目录
    build_dir = os.path.join(root_dir, "build")
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)
    path_arr = ["ios","android","native"]
    #如果是有效地路径创建
    if platform in path_arr:
        # platform目录
        global platform_dir
        if platform == "android":
            if args.abi == None:
                for android_abi in android_abis:
                    createDir(build_dir, android_abi)
            else:
                createDir(build_dir,args.abi)
        elif platform == "native":
            if sys.platform == "win32":
                platform_dir = os.path.join(build_dir, platform+"/win32")
            else:
                platform_dir = os.path.join(build_dir, platform + "/mac")
            if not os.path.exists(platform_dir):
                os.makedirs(platform_dir)
        else:
            if args.abi == None:
                for ios_platform in ios_platforms:
                    createDir(build_dir, ios_platform)
            else:
                createDir(build_dir, args.abi)
        return True
    else:
        return False
def main():
    args = build_parser()
    print(sys.platform)
    global android_abis
    android_abis = ["x86","armeabi-v7a","arm64-v8a","x86_64"]
    global ios_platforms
    ios_platforms = ["OS"]
    # ios_platforms = ["SIMULATOR64", "OS"]
    #因为platform比较常用还是用全局比较好
    global platform
    platform = args.platform
    global is_debug
    is_debug = False
    if args.debug == "y" or args.debug == "Y":
        is_debug = True
    # is_debug = args.debug
    #输入的平台无效时候，不执行后续的步骤
    if makeDir(args) == False:
        print("invoid platform please input again")
        return

    if args.buildOnly != "y":
        #生成modifile
        generateProject(args)
    
    #编译
    buildProject(args)

    

if __name__ == '__main__':
    main()