set(EXECUTABLE_OUTPUT_PATH ../bin/gtest_demo)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

find_package(Threads)
if (LINUX)
    SET(USE_LIBS pthread gtest gtest_main gmock)
else()
    SET(USE_LIBS gtest gtest_main gmock)
endif()
add_executable(assert assert.cpp)
target_link_libraries(assert ${USE_LIBS})
add_executable(event event.cpp)
target_link_libraries(event ${USE_LIBS})
add_executable(param param.cpp)
target_link_libraries(param ${USE_LIBS})

add_executable(death death.cpp)
target_link_libraries(death ${USE_LIBS})

add_executable(mock mock.cpp)
target_link_libraries(mock ${USE_LIBS})

find_package(GTest REQUIRED)
include(GoogleTest)
include(CTest)

gtest_add_tests(
        TARGET assert
        TEST_SUFFIX .noArgs
        TEST_LIST noArgsTests
)

gtest_add_tests(
        TARGET event
        TEST_SUFFIX .noArgs
        TEST_LIST noArgsTests
)
gtest_add_tests(
        TARGET param
        TEST_SUFFIX .noArgs
        TEST_LIST noArgsTests
)
gtest_add_tests(
        TARGET mock
        TEST_SUFFIX .noArgs
        TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)

#set(UNIT_TEST assert)
#add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})
#add_custom_command(
#        TARGET ${UNIT_TEST}
#        COMMENT "Run tests"
#        POST_BUILD
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^${UNIT_TEST}$" --output-on-failures
#)
