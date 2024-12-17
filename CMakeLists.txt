cmake_minimum_required(VERSION 3.29)
project(arbre_largeur)

set(CMAKE_CXX_STANDARD 26)

add_executable(arbre_largeur main.cpp
        BinaryTree.cpp
        BinaryTree.h
        VectorTree.cpp
        VectorTree.h)
