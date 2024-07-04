cmake_minimum_required(VERSION 3.26)

set (solution_path "${CMAKE_CURRENT_SOURCE_DIR}")

function (assign_group)
    set( _OPTIONS_ARGS )
    set( _ONE_VALUE_ARGS PRJ_PATH FOLDER_PRX)
    set( _MULTI_VALUE_ARGS SOURCE_FILES)
    cmake_parse_arguments( ASSIGN_GROUP "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN} )

    foreach(_source ${ASSIGN_GROUP_SOURCE_FILES})
        string (REGEX MATCH "${ASSIGN_GROUP_PRJ_PATH}/([A-z]+)/[A-z]+.[c/h]*" _ "${_source}")
        if ("${CMAKE_MATCH_1}" STREQUAL "")
            continue()
        endif()
        source_group ("${ASSIGN_GROUP_FOLDER_PRX}\\${CMAKE_MATCH_1}" FILES "${_source}")
    endforeach()
endfunction()

function (set_project _project_name _project_path)
#setting sources and making filters
    set (src "${_project_path}/src")
    set (inc "${_project_path}/include")
    file(GLOB_RECURSE src_list
        LIST_DIRECTORIES FALSE
        "${src}/*.c*"
        )
    file(GLOB_RECURSE h_list
        LIST_DIRECTORIES FALSE
        "${inc}/*.h*"
        )

    set (SOURCES ${h_list} ${src_list})
    add_executable (${_project_name} ${SOURCES})
    assign_group (TARGETS PRJ_PATH ${src} FOLDER_PRX "Source Files" SOURCE_FILES ${src_list})
    assign_group (TARGETS PRJ_PATH ${inc} FOLDER_PRX "Header Files" SOURCE_FILES ${h_list})

    set_target_properties (${_project_name} PROPERTIES 
                           CXX_STANDARD_REQUIRED TRUE
                           CXX_STANDARD 20
                           VS_DEBUGGER_ENVIRONMENT "PATH=${solution_path}/3rdparty/lib;%PATH%"
                          )

    target_include_directories (${_project_name} PRIVATE "${solution_path}/3rdparty/include"
                                                         "${_project_path}/include")
    target_link_directories (${_project_name} PRIVATE "${solution_path}/3rdparty/lib")

endfunction()

#Set up solution
project(Tetris)

#===========================
# Tetris Project
#===========================
set_project (Tetris "${solution_path}/tetris")
target_link_libraries (Tetris raylib
                              winmm)


#===========================
# Test Project
#===========================

set_project (Test "${solution_path}/test")

target_include_directories (Test PRIVATE "${solution_path}/tetris/include")
target_link_libraries (Test gtest)
