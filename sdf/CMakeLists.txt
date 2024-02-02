#cmake最低版本支持
cmake_minimum_required (VERSION 3.4)

#cmake工程名称
project (SDFFont)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

#指定runtimelibray类型
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT")
endif()

include(engine_export/cmake/platform.cmake)

include(engine_export/lua/CMakeLists.txt)
include(engine_export/babe/CMakeLists.txt)

#msdf库的CMakeList
include(sdf_lib/CMakeLists.txt)

#将目录下的文件添加到一个变量
set(SDFFont_SRC
    main.cpp
	SDFLoader.cpp
    )

include_directories(./ ${BABE_INCLUDE_DIR} ${LUA_INCLUDE_DIR})

#附加的freetype和msdf的include目录
include_directories(msdf-atlas-gen/artery-font-format)
include_directories(msdf-atlas-gen/msdfgen)
include_directories(msdf-atlas-gen/msdfgen/freetype/include)
include_directories(msdf-atlas-gen/msdfgen/include)
include_directories(msdf-atlas-gen/msdf-atlas-gen)

#IOS下编译成静态库.a
if (IOS)
    add_library(SDFFont STATIC ${SDFFont_SRC})
else()
    #android windows下编译成动态库 so dll
    add_library(SDFFont SHARED ${SDFFont_SRC})
    if(ANDROID)
        add_custom_command(
            TARGET SDFFont POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    libSDFFont.so
                    libSDFFont_unstrip.so)
        add_custom_command(TARGET SDFFont POST_BUILD COMMAND
            ${CMAKE_STRIP} libSDFFont.so)
    endif(ANDROID)
endif()

#链接额外的第三方库
target_link_libraries(SDFFont ${LUA_LIBRARY} ${BABE_LIBRARY} ${FREETYPE_LIBRARY} ${MSDF_ATLAS_GEN_LIBRARY} ${MSDF_GEN_CORE_LIBRARY} ${MSDF_GEN_EXT_LIBRARY})


install(TARGETS SDFFont DESTINATION lib)
