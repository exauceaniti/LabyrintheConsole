# Définition de la version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Nom du projet et version
project(LabyrintheConsole VERSION 1.0)

# Spécifie le standard C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajoute les dossiers include au chemin des headers
include_directories(include)

# Fichiers source du projet
set(SOURCES
        src/Labyrinthe.cpp
        src/Joueur.cpp
        src/GameEngine.cpp
        src/Affichage.cpp
        src/Utils.cpp
        main.cpp
)

# Création de l’exécutable
add_executable(LabyrintheConsole ${SOURCES})

# Threads si nécessaire (ex: futurs ajouts multithread)
find_package(Threads REQUIRED)
target_link_libraries(LabyrintheConsole Threads::Threads)
