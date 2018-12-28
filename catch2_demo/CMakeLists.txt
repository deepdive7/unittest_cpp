set(EXECUTABLE_OUTPUT_PATH ../bin/catch2_demo)
find_package(Catch2 REQUIRED)
add_executable(require require.cpp)
add_executable(section section.cpp)
target_link_libraries(require Catch2::Catch2)
target_link_libraries(section Catch2::Catch2)

INCLUDE(CTest)
INCLUDE(Catch)

catch_discover_tests(require)
catch_discover_tests(section)
