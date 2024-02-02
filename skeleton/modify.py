#!/usr/bin/env python
# coding: utf-8
import os, sys
import shutil
import socket
import argparse
import re
 #替换字符串
def replace_project_pbxproj(filepath,key_string,wFilePath):
    f1 = open(filepath, "rb")
    content = ""
    for line in f1:
        strline = line.decode('utf8')
        # print(strline)
        str_arr = strline.split(key_string)
        # print(str_arr)
        # arr = line.split(key_string)
        # print(str_arr)
        line_str = ""
        count = len(str_arr) - 1
        for i in range(0,len(str_arr)):
            str = str_arr[i]
            temp_str = "L"+str
            if i == count:
                line_str = line_str + temp_str
            else:
                line_str = line_str + temp_str + ", "
        # print(line_str)
        content += line_str
    
    f1.close()
    f2 = open(wFilePath, "wb")
    f2.write(content.encode('utf8'))
    f2.close()
    # f1.close()
    # f2 = open(filepath, "wb")
    # f2.write(content.encode('utf8'))
    # f2.close()
if __name__ == "__main__":
    file_path = "./pinyin.m"
    file_path2 = "./pinyin2.m"
    split_str = ", "
    replace_project_pbxproj(file_path,split_str,file_path2)
