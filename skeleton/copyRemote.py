#!/usr/bin/env python
# coding: utf-8
import os, sys
import shutil
import socket
import argparse
import re
def build_parser():
    parser = argparse.ArgumentParser()
    # parser.add_argument('-e', '--event',required=True,help='1:camake generate,2:camake build')
    # parser.add_argument('-n', '--plugin_name',required=True, help='the plugins name')
    parser.add_argument('-p', '--platform',required=True, help='copy platform')
    parser.add_argument('-v', '--version',required=True, help='plugin version')
    parser.add_argument('-b', '--branch',required=False, help='branch version')
    args = parser.parse_args()

    return args
 #替换字符串
def replace_project_pbxproj(filepath, key_string, value_string):
    if key_string is None or value_string is None:
        raise TypeError

    content = ""
    f1 = open(filepath, "rb")
    for line in f1:
        strline = line.decode('utf8')
        if key_string in strline:
            str_arr = strline.split(key_string)
            new_line_str = str_arr[0] + key_string + " " + value_string + "\n"
            content += new_line_str
        else:
            content += strline
    f1.close()
    f2 = open(filepath, "wb")
    f2.write(content.encode('utf8'))
    f2.close()
def func_copy(primary_dir, target_dir):  # 拷贝方法 把原始文件夹的所有文件夹和文件 按照同样的名字拷贝到目标文件夹中
    # 遍历filepath下所有文件,包括目录
    files = os.listdir(primary_dir)
    for i in files:  # i 是目录下的文件或文件夹
        path = os.path.join(primary_dir, i)  # 字符串拼接
        i_new = os.path.join(target_dir, i)  # 目标文件夹也要改变
        if ".so" in path and not "unstrip." in path:
            shutil.copyfile(path, i_new)
        if ".a" in path:
            shutil.copyfile(path, i_new)
def copyAndroid():
    android_dir = "./build/android/"
    target_dir = "platform/android/skeleton/src/main/jniLibs/"
    for arch in ['armeabi-v7a', 'arm64-v8a', 'x86_64', 'x86']:
        if not os.path.exists(target_dir+arch):  # 如果没新建过 新建同名目标文件夹
                os.makedirs(target_dir+arch)
        func_copy(android_dir+arch,target_dir+arch)
def modifyAndroidVersion(version_str):
    gradle_path = "platform/android/skeleton/build.gradle"
    replace_project_pbxproj(gradle_path,"version =",version_str)
    os.chdir("platform/android")   #修改当前工作目录
    os.system("chmod 777 gradlew")
    os.system("gradlew publishProductionPublicationToNexusRepository")
def modifyIOSVersion(version_str):
    podspec_path = "platform/ios/SkeletonKit.podspec"
    replace_project_pbxproj(podspec_path,"s.version          =",version_str)

    os.chdir("platform/ios")   #修改当前工作目录
    os.system("sh ./push.sh " + version_str)
def copyIos():
    ios_dir = "./build/ios"
    target_dir = "platform/ios/SkeletonKit"
    func_copy(ios_dir,target_dir)

if __name__ == "__main__":
    # print("________________________startcopy_____________________")
    args = build_parser()
    # #打开文件服务器
    # os.system("osascript -e 'mount volume \"smb://boyaa.com/bydfs\"'")

    # global plugin_dir
    # if args.is_upload and args.is_upload.upper() == "YES":
    #     plugin_dir = "/Users/boyaa/enginers/v6.0/runtime"
    # else:
    #     plugin_dir = r"/Volumes/bydfs/临时共享(保留3天)/IDE/plugins/" + args.plugin_name
    os.chdir("platform/ios")   #修改当前工作目录
    os.system("git reset --hard")
    os.system("git checkout .&& git clean -xdf")
    os.system("git checkout master")
    os.system("git pull")

    os.chdir("../../")   #修改当前工作目录
    # os.chdir("git submodule update") 
    # print(plugin_dir)
    # if not os.path.exists(plugin_dir):
    #     os.makedirs(plugin_dir)
    if args.platform == "ios":
        copyIos()
        ver_str = "'" + args.version + "'"
        modifyIOSVersion(ver_str)
        # os.chdir("../../")   #修改当前工作目录
        # os.system("git pull")
        # os.system("git status")
        # os.system("git add .")
        # os.system("git commit -m " + args.version)
        # os.system("git push origin newPlugin")
    elif args.platform == "android":
        copyAndroid()
        ver_str = '"' + args.version + '"'
        modifyAndroidVersion(ver_str)

    # if args.is_upload and args.is_upload.upper() == "YES":
    #     print("______________________________________commit begin_________________________________________")
    #     version_str = readVersionNumber()
    #     log_str = "version:" + version_str
    #     os.system('''cd /Users/boyaa/enginers/v6.0;svn update;svn add . --no-ignore --force;''')
    #     order_str = '''cd /Users/boyaa/enginers/v6.0;svn commit -m ''' + log_str
    #     os.system(order_str)
    #     print("______________________________________commit end___________________________________________")
        # os.system('''cd /Users/boyaa/enginers/v6.0;''')