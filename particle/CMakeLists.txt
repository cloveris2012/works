cmake_minimum_required (VERSION 3.4)
project (particle)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

include(engine_export/cmake/platform.cmake)
include(engine_export/lua/CMakeLists.txt)
include(engine_export/babe/CMakeLists.txt)
if(MACOSX OR LINUX)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

set(EXAMPLE_SRC
    main.cpp
particle/Emitter.cpp
particle/FloatConstantCurve.cpp
particle/FloatDistri.cpp
particle/FloatUniformCurve.cpp
particle/Particle.cpp
particle/random.cpp
particle/template.cpp
particle/VectorConstantCurve.cpp
particle/VectorDistri.cpp
particle/VectorUniformCurve.cpp
particle/ParticleEvent.cpp
particle/ParticleLoader.cpp
particle/data/EmitterData.cpp
particle/data/FloatDistriData.cpp
particle/data/VectorDistriData.cpp
particle/data/ParticleEventData.cpp
    )

include_directories(./ ./particle ./particle/data ${BABE_INCLUDE_DIR} ${LUA_INCLUDE_DIR})
if (IOS)
    add_library(particle STATIC ${EXAMPLE_SRC})
else()
    add_library(particle SHARED ${EXAMPLE_SRC})
    if(ANDROID)
        add_custom_command(
            TARGET particle POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    libparticle.so
                    libparticle_unstrip.so)
                    
        add_custom_command(TARGET particle POST_BUILD COMMAND
            ${CMAKE_STRIP} libparticle.so)
    endif(ANDROID)
endif()
target_link_libraries(particle ${LUA_LIBRARY} ${BABE_LIBRARY})
install(TARGETS particle DESTINATION lib)
