cmake_minimum_required (VERSION 3.4)
project (skeleton)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

include(engine_export/cmake/platform.cmake)
include(engine_export/lua/CMakeLists.txt)
include(engine_export/babe/CMakeLists.txt)

file (GLOB_RECURSE SKELETON_SOURCE_FILES src/*.cpp)
file (GLOB_RECURSE SKELETON_HEADER_FILES src/*.h)

if(MACOSX OR LINUX)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

if (WIN32)
    MACRO(SOURCE_GROUP_BY_FOLDER)        # 将源文件和头文件进行分组
      SET(SOURCE_GROUP_DELIMITER "/")
      SET(last_dir "")
      SET(files "")
      FOREACH(file ${SKELETON_SOURCE_FILES} ${SKELETON_HEADER_FILES})
        file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}" ${file})
        GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
        IF (NOT "${dir}" STREQUAL "${last_dir}")
          IF (files)
            SOURCE_GROUP("${last_dir}" FILES ${files})
          ENDIF (files)
          SET(files "")
        ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
        SET(files ${files} ${file})
        SET(last_dir "${dir}")
      ENDFOREACH(file)
      IF (files)
        SOURCE_GROUP("${last_dir}" FILES ${files})
      ENDIF (files)
    ENDMACRO(SOURCE_GROUP_BY_FOLDER)
    SOURCE_GROUP_BY_FOLDER()
    SOURCE_GROUP("" FILES main.cpp)
endif()

set(EXAMPLE_SRC
    main.cpp
    ${SKELETON_HEADER_FILES}
    ${SKELETON_SOURCE_FILES}
    )

include_directories(./ ${BABE_INCLUDE_DIR} ${LUA_INCLUDE_DIR})

set (3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)
set (GLM_DIR ${3RD_DIR}/glm)
include_directories (${GLM_DIR})

include_directories (${PROJECT_SOURCE_DIR}/src)

if (IOS)
    add_library(skeleton STATIC ${EXAMPLE_SRC})
else()
    add_library(skeleton SHARED ${EXAMPLE_SRC})
    if(ANDROID)
        add_custom_command(TARGET skeleton POST_BUILD COMMAND
            ${CMAKE_STRIP} libskeleton.so)
    endif(ANDROID)
endif()
target_link_libraries(skeleton ${LUA_LIBRARY} ${BABE_LIBRARY})
install(TARGETS skeleton DESTINATION lib)
