#
# This file is part of C11_TEMPLATE.
#

############################################################
# Application includes
############################################################
list(APPEND APP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

############################################################
# Append libraries
############################################################
list(APPEND APP_LIBRARIES
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
)

############################################################
# Add the external project sources
############################################################
list(APPEND APP_EXTERNAL_SOURCES
    ${GL3W_SOURCES}
)
list(APPEND APP_INCLUDES
    ${OPENGL_INCLUDE_DIR}
    ${GL3W_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
)
list(APPEND APP_LIBRARIES
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_MAIN_LIBRARY}
)

############################################################
# Append sources
############################################################
list(APPEND APP_SOURCES
    common.c
    main.c
)

############################################################
# Generate the version file
############################################################
include(GetGitRevisionDescription)
git_describe(GIT_HASH)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h
)

############################################################
# Append the executable
############################################################
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${APP_SOURCES} ${APP_EXTERNAL_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${APP_SOURCES} ${APP_EXTERNAL_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} ${APP_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${APP_INCLUDES})
