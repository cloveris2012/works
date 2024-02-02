#!/bin/sh
source ~/.bash_profile


WORKSPACE=$1
Build_Platform=$2
Build_Version=$3
build_path="$WORKSPACE/build"
echo $build_path
if [ -d "$build_path" ]
then
    echo "build_path_________________"
    rm -rf $build_path
fi

echo "__________________________beginplugin__________________"
native_str="native"
android_str="android"
ios_str="ios"
all_str="all"
true_str="true"
false_str="false"
mobile_str="mobile"
Build_Success="false"
#查找libraly是否编译完成
findFileIsExist(){
    Build_Success="false"
    TEMP_PATH=${1}
    FIND_STR=${2}
    files=$(ls $TEMP_PATH)
    for filename in $files
    do
        if [[ $filename =~ $FIND_STR ]]
        then
            Build_Success="true"
            break
        else
            Build_Success="false"
        fi
    done
}
#编译ios
doIosBuild(){
    echo "_________________________build_ios_platform__________________"
    python ./BuildPlugin.py -p ios
    echo "_________________________end_ios_platform__________________"
    ios_path="$WORKSPACE/build/ios"
    find_str=".a"
    findFileIsExist $ios_path $find_str
    if [ $Build_Success == $true_str ]
    then
        echo "_________________________success_ios_platform__________________"
        echo "_________________________begin_copy_ios__________________"
        # python ./copyTemp.py -p $Build_Platform -n $JOB_NAME -u no
        echo $Build_Platform
        echo $Build_Version
        python copyRemote.py -p ios -v $Build_Version 
        echo "_________________________end_copy_ios__________________"
    else
        echo "_________________________fail_copy_ios__________________"
        exit 1
    fi

}
#编译android
doAndroidBuild(){
    echo "_________________________build_android_platform__________________"
    python ./BuildPlugin.py -p android
    echo "_________________________end_andorid_platform__________________"
    android_path="$WORKSPACE/build/android/armeabi-v7a"
    find_str=".so"
    findFileIsExist $android_path $find_str
    if [ $Build_Success == $true_str ]
    then
        echo "_________________________success_android_platform__________________"
        echo "_________________________begin_copy_android__________________"
        # python ./copyTemp.py -p $Build_Platform -n $JOB_NAME -u no
        echo $Build_Platform
        echo $Build_Version
        python copyRemote.py -p android -v $Build_Version
        echo "_________________________end_copy_android__________________"
        $symuploader upload -src ./build/android -emails YuchengMo@boyaa.com,VicentGong@boyaa.com,RaytionWu@boyaa.com,Tonyzz@boyaa.com
    else
        echo "_________________________fail_android_platform___________________"
        exit 1
    fi
}
#编译native
doNativeBuild(){
    echo "_________________________build_mac_platform__________________"
    python ./BuildPlugin.py -p native
    echo "_________________________end_mac_platform__________________"
    mac_path="$WORKSPACE/build/native/mac"
    find_str=".dylib"
    findFileIsExist $mac_path $find_str
    if [ $Build_Success == $true_str ]
    then
        echo "_________________________success_mac_platform__________________"
        echo "_________________________begin_copy_mac__________________"
        python copyTemp.py -p $Build_Platform -n $JOB_NAME -u no
        echo "_________________________end_copy_mac__________________"
    else
        echo "_________________________fail_mac_platform___________________"
        exit 1
    fi
}
#根据构建参数，选择构建平台
if [ $Build_Platform == $native_str ]
then
    doNativeBuild
elif [ $Build_Platform == $android_str ]
then
    doAndroidBuild
elif [ $Build_Platform == $ios_str ]
then
    doIosBuild
elif [ $Build_Platform == $mobile_str ]
then
	doIosBuild
    doAndroidBuild
    
elif [ $Build_Platform == $all_str ]
then
	doNativeBuild
    doIosBuild
    doAndroidBuild
else
	echo "_________________________error_platform__________________"
    exit 1
fi