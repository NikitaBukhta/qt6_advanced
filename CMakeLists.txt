cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "main cmake list")
project(${PROJECT_NAME})

# Get the current CMakeLists.txt directory
get_filename_component(CURRENT_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)

# Get a list of directories within the current directory, excluding .vscode and build
file(GLOB CURRENT_DIRECTORIES LIST_DIRECTORIES true "${CURRENT_DIR}/*")

# Iterate over the directories and print their names
foreach(dir ${CURRENT_DIRECTORIES})
    if(IS_DIRECTORY ${dir})
        get_filename_component(dir_name ${dir} NAME)
        if(NOT dir_name STREQUAL ".vscode" AND NOT dir_name STREQUAL "build" AND NOT dir_name STREQUAL ".git")
            message(STATUS "Directory name: ${dir_name}")
            add_subdirectory(${dir_name})
        endif()
    endif()
endforeach()
