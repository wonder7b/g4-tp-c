cmake_minimum_required(VERSION 3.30)
project(g4_tp_c C)

set(CMAKE_C_STANDARD 11)

add_executable(
        g4_tp_c
        main.c
        structures.h
        utils.c
        fonctions.c
        guide.c
        visiteur.c
)
