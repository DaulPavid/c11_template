#
# This file is part of C11_TEMPLATE.
#

############################################################
# Include source directories
############################################################
list(APPEND TEST_INCLUDES 
    ${CMAKE_SOURCE_DIR}/src
)

list(APPEND SOURCES 
    ${CMAKE_SOURCE_DIR}/src/common.c
)

############################################################
# Add testing source files
############################################################
list(APPEND TEST_SOURCES
    test_common.c
)

############################################################
# Add testing executables
############################################################
foreach(TEST ${TEST_SOURCES})
    string(REPLACE ".c" "" TEST_NAME ${TEST})
    add_executable(${TEST_NAME} ${TEST} ${SOURCES} unit_test.c)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    target_include_directories(${TEST_NAME} PRIVATE ${TEST_INCLUDES})
endforeach()
