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
    parser.add_argument('-n', '--plugin_name',required=True, help='the plugins name')
    parser.add_argument('-p', '--platform',required=True, help='copy platform')
    parser.add_argument('-u', '--is_upload',required=False, help='upload platform')
    args = parser.parse_args()

    return args

def copyIos():
    ios_path = "/ios"
    ios_dir = "./build" + ios_path
    ios_files = os.listdir(ios_dir)
    if not os.path.exists(plugin_dir+ios_path):
        os.makedirs(plugin_dir+ios_path)
    for file in ios_files:
        if ".a" in file:
            shutil.copyfile(ios_dir+"/"+file, plugin_dir+ios_path+"/"+file)
def copyMac():
    mac_path = "/native/mac"
    mac_dir = "./build" + mac_path
    mac_files = os.listdir(mac_dir)
    if not os.path.exists(plugin_dir+mac_path):
        os.makedirs(plugin_dir+mac_path)
    
    for root, dirs, files in os.walk(mac_dir):
        for dir in dirs:
            print("os.walk(mac_dir)__________________")
            src_dir = os.path.join(root,dir)
            dst_dir = src_dir.replace("./build","")
            boyaa_dir = plugin_dir+dst_dir
            print("src_dir______________________"+src_dir)
            print("boyaa_dir____________________"+boyaa_dir)
            if not os.path.exists(boyaa_dir):
                os.makedirs(boyaa_dir)
        for file in files:
            print("os.walk(mac_file)__________________")
            src_file = os.path.join(root, file)
            dst_file = src_file.replace("./build","")
            print(src_file)
            print(plugin_dir+dst_file)
            shutil.copyfile(src_file, plugin_dir+dst_file)
def copyAndroid():
    for arch in ['armeabi-v7a', 'arm64-v8a', 'x86_64', 'x86']:
        if not os.path.exists(plugin_dir+"/android/" + arch):
            os.makedirs(plugin_dir+"/android/" + arch)
        abi_path = "/android/" + arch
        abi_dir = "./build" + abi_path
        abi_files = os.listdir(abi_dir)
        for file in abi_files:
            if ".so" in file:
                print(abi_dir+"/"+file)
                print(plugin_dir+abi_path+"/"+file)
                shutil.copyfile(abi_dir+"/"+file, plugin_dir+abi_path+"/"+file)
def readVersionNumber():
    version_file_path = "/Users/boyaa/Desktop/myc/engine/jenkins/src/base/version.h"
    version_str = ""
    with open(version_file_path,"r") as f:

        for line in f:
            if "MAJOR" in line:
                str = splitVersionStr(line,"MAJOR")
                version_str = version_str + str
            if "MINOR" in line:
                str = splitVersionStr(line,"MINOR")
                version_str = version_str + "_" + str
            if "REVISION" in line:
                str = splitVersionStr(line,"REVISION")
                version_str = version_str + "_" + str
    return version_str

def splitVersionStr(line,split_str):
    rs = line.strip('\n')
    arr = rs.split(split_str,1)
    v_str = arr[1]
    re.sub(r"\s+", "", v_str)
    v_str = v_str.replace(' ', '')
    return v_str

if __name__ == "__main__":
    print("________________________startcopy_____________________")
    args = build_parser()
    #打开文件服务器
    os.system("osascript -e 'mount volume \"smb://boyaa.com/bydfs\"'")

    global plugin_dir
    if args.is_upload and args.is_upload.upper() == "YES":
        plugin_dir = "/Users/boyaa/enginers/v6.0/runtime"
    else:
        plugin_dir = r"/Volumes/bydfs/临时共享(保留3天)/IDE/plugins/" + args.plugin_name
    
    print(plugin_dir)
    if not os.path.exists(plugin_dir):
        os.makedirs(plugin_dir)
    if args.platform == "ios":
        copyIos()
    elif args.platform == "android":
        copyAndroid()
    elif args.platform == "mobile":
        copyIos()
        copyAndroid()
    elif args.platform == "all":
        copyIos()
        copyAndroid()
        copyMac()
    elif args.platform == "native":
        if sys.platform == "win32":
            print("copy win")
        else:
            copyMac()

    if args.is_upload and args.is_upload.upper() == "YES":
        print("______________________________________commit begin_________________________________________")
        version_str = readVersionNumber()
        log_str = "version:" + version_str
        os.system('''cd /Users/boyaa/enginers/v6.0;svn update;svn add . --no-ignore --force;''')
        order_str = '''cd /Users/boyaa/enginers/v6.0;svn commit -m ''' + log_str
        os.system(order_str)
        print("______________________________________commit end___________________________________________")
        # os.system('''cd /Users/boyaa/enginers/v6.0;''')
    