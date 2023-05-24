cmake_minimum_required(VERSION 3.24)
project(hw3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hw3
        glob.h
        lex.yy.c
        main.c
        printerror.c
        printtoken.c
        reporterror.c
        symboltable.c
        tn.h
        parser.tab.c
        parser.tab.h
        reporterror.c)
