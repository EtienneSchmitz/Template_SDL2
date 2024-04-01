cmake_minimum_required(VERSION 3.8)
project(Template_SDL2)

set(CMAKE_C_STANDARD 99)

if(WIN32)
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

    # Configuration SDL_mixer
    set(SDL2_MIXER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_mixer/")
    set(SDL2_MIXER_INCLUDE_DIRS "${SDL2_MIXER_DIR}/include")
    set(SDL2_MIXER_LIBRARIES "${SDL2_MIXER_DIR}/lib/x64/SDL2_mixer.lib")
    set(SDL2_MIXER_DLL_PATH "${SDL2_MIXER_DIR}/lib/x64")

    # Configuration SDL_TTF
    set(SDL2_TTF_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL2_ttf/")
    set(SDL2_TTF_INCLUDE_DIRS "${SDL2_TTF_DIR}/include")
    set(SDL2_TTF_LIBRARIES "${SDL2_TTF_DIR}/lib/x64/SDL2_ttf.lib")
    set(SDL2_TTF_DLL_PATH "${SDL2_TTF_DIR}/lib/x64")

elseif(APPLE)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
endif()

# Les source et les .h
include_directories(include)

set (SOURCES
    src/main.c
    # Ici pour les autres fichiers sources


)


# Installation de la librarie SDL2
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL2_INCLUDE_DIRS} *
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)


# Copie SDL2.dll et SDL2_image.dll dans le répertoire de sortie après la construction (pour Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DLL_PATH}/SDL2.dll"
        "${SDL2_IMAGE_DLL_PATH}/SDL2_image.dll"
        "${SDL2_MIXER_DLL_PATH}/SDL2_mixer.dll"
        "${SDL2_TTF_DLL_PATH}/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E echo "Copying assets to $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)