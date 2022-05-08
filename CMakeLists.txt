cmake_minimum_required(VERSION 3.5)

project(01.lesson_3)

add_executable(lesson_3 
    util.cpp
    main.cpp
    winner.cpp
    game.cpp
    winner.h
    main.h
    util.h
    game.h
)

set_target_properties(lesson_3 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS lesson_3)