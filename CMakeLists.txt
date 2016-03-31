cmake_minimum_required (VERSION 2.8)
project (hmr)
 
# The version number.
set (hmr_VERSION_MAJOR 0)
set (hmr_VERSION_MINOR 1)

include(CheckCXXCompilerFlag)
enable_language(CXX)

install (DIRECTORY include/hmr DESTINATION include)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -VV -C ${CMAKE_CFG_INTDIR})

function(add_test_executable TEST_NAME)
    add_executable (${TEST_NAME} EXCLUDE_FROM_ALL ${ARGN})
    if(WIN32)
        add_test(NAME ${TEST_NAME} WORKING_DIRECTORY ${LIBRARY_OUTPUT_PATH} COMMAND ${TEST_NAME}${CMAKE_EXECUTABLE_SUFFIX})
    else()
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
    add_dependencies(check ${TEST_NAME})
    set_tests_properties(${TEST_NAME} PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
endfunction(add_test_executable)

function(create_executable NAME CONTENT)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.cpp "${CONTENT}")
    add_executable(${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.cpp)
endfunction()

function(create_test_executable NAME CONTENT)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.cpp "${CONTENT}")
    add_test_executable(${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.cpp)
endfunction()

function(add_test_header TEST_NAME HEADER)
    create_test_executable(header-include-${TEST_NAME} 
        "#include <${HEADER}>\nint main() {}\n"
    )
endfunction(add_test_header)

function(add_test_static_header TEST_NAME HEADER)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/header-main-include-${TEST_NAME}.cpp 
        "#include <${HEADER}>\nint main() {}\n"
    )
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/header-static-include-${TEST_NAME}.cpp 
        "#include <${HEADER}>\n"
    )
    add_test_executable(header-static-include-${TEST_NAME} 
        ${CMAKE_CURRENT_BINARY_DIR}/header-main-include-${TEST_NAME}.cpp 
        ${CMAKE_CURRENT_BINARY_DIR}/header-static-include-${TEST_NAME}.cpp
    )
endfunction(add_test_static_header)

include(CTest)

include_directories(include)

file(GLOB TESTS test/*.cpp)
foreach(TEST ${TESTS})
    get_filename_component(BASE_NAME ${TEST} NAME_WE)
    add_test_executable(${BASE_NAME} ${TEST})
endforeach()

file(GLOB HEADERS include/hmr/*.hpp)
foreach(HEADER ${HEADERS})
    get_filename_component(BASE_NAME ${HEADER} NAME_WE)
    add_test_header(${BASE_NAME} hmr/${BASE_NAME}.hpp)
endforeach()


