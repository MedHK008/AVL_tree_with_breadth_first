cmake_minimum_required(VERSION 3.29)
project(arbre_largeur)

# set(CMAKE_CXX_STANDARD 26)

# set(SFML_DIR "C:/SFML")

# Find SFML package
# find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(arbre_largeur main.cpp
        BinaryTree.cpp
        BinaryTree.h
        Heap.cpp
        Heap.h
        Graph.cpp
        Graph.h
)

# Link SFML libraries
# target_link_libraries(arbre_largeur sfml-graphics sfml-window sfml-system)
