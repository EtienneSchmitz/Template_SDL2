cmake_minimum_required(VERSION 3.8)
project(Template_SDL2)

set(CMAKE_C_STANDARD 99)

# Configuration SDL
set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2/")
set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")
set(SDL2_DLL_PATH "${SDL2_DIR}/lib/x64")

# Configuration SDL_image
set(SDL2_IMAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_image/")
set(SDL2_IMAGE_INCLUDE_DIRS "${SDL2_IMAGE_DIR}/include")
set(SDL2_IMAGE_LIBRARIES "${SDL2_IMAGE_DIR}/lib/x64/SDL2_image.lib")
set(SDL2_IMAGE_DLL_PATH "${SDL2_IMAGE_DIR}/lib/x64")

# Les source et les .h
include_directories(include)
file(GLOB SOURCES "src/*.c") 

# Installation de la librarie SDL2
add_executable(Template_SDL2 ${SOURCES})
target_include_directories(Template_SDL2 PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(Template_SDL2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})


# Copie SDL2.dll et SDL2_image.dll dans le répertoire de sortie après la construction (pour Windows)
if(WIN32)
    add_custom_command(TARGET Template_SDL2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DLL_PATH}/SDL2.dll"
        "${SDL2_IMAGE_DLL_PATH}/SDL2_image.dll"
        $<TARGET_FILE_DIR:Template_SDL2>)
endif()