#--------------------------- MAIN CONFIGURATION ---------------------------#

cmake_minimum_required(VERSION 3.6.0)
set(PROJECT_NAME qt6_learning)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Set the directory where .cpp files are located;

# Get a list of all .cpp files recursively within the directory
file(GLOB_RECURSE CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(
    ${PROJECT_NAME}
    ${CPP_SOURCES}
)

#----------------------------- LINK LIBRARIES -----------------------------#

#link QT6

find_package(Qt6 REQUIRED COMPONENTS Core)
# Add the Qt 6 include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${Qt6Core_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)

# Verify the minimum required version of Qt
if(Qt6_FOUND)
    if(Qt6_VERSION VERSION_LESS 6.0.0)
        message(FATAL_ERROR "Minimum required version of Qt is 6.0.0")
    endif()
else()
    message(FATAL_ERROR "Qt6 package not found. Please ensure Qt 6 is installed.")
endif()