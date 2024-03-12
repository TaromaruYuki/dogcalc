cmake_minimum_required(VERSION 3.10)

project(DogCalc VERSION 1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(SOURCES 
    src/main.cpp
    src/application.cpp
    src/application.h
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARY_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER})