cmake_minimum_required(VERSION 3.10)
project(Template_SDL2)

set(CMAKE_C_STANDARD 17)

# Ajout SDL
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

# Fichiers sources et headers
include_directories(include)

set (SOURCES
    src/main.c
    # Ici pour les autres fichiers sources
)

# Installation de la librarie SDL2
add_executable(Template_SDL2 ${SOURCES})
target_include_directories(Template_SDL2 
    PRIVATE 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
)
target_link_libraries(Template_SDL2 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES}
)