cmake_minimum_required(VERSION 3.1)
project(unittest_demo)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
LIST(APPEND CMAKE_PREFIX_PATH "/usr/local")

set(EXECUTABLE_OUTPUT_PATH bin)
set(INC_DIR C:/Soft/cpp3rd/include)
set(LINK_DIR C:/Soft/cpp3rd/lib)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(gmock gtest)
enable_testing()

set(RUN_GTEST 1)
set(RUN_CATCH2 1)
if (RUN_GTEST)
    add_subdirectory(gtest_demo)
endif()

if (RUN_CATCH2)
    add_subdirectory(catch2_demo)
endif()
