cmake_minimum_required(VERSION 3.10)
project(LabyrintheConsole)

set(CMAKE_CXX_STANDARD 17)

# Liste tous les fichiers sources
file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "main.cpp"
)

# Crée l'exécutable
add_executable(LabyrintheConsole ${SOURCES})

# Configure les inclusions
target_include_directories(LabyrintheConsole PRIVATE include)

# Optionnel : pour les threads
find_package(Curses REQUIRED)
target_link_libraries(LabyrintheConsole PRIVATE ${CURSES_LIBRARIES})