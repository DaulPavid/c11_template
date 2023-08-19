#
# This file is part of RogueBuild.
#

############################################################
# Add gl3w sources and includes
############################################################
list(APPEND GL3W_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/gl3w.c)
list(APPEND GL3W_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GL3W_SOURCES "${GL3W_SOURCES}" PARENT_SCOPE)
set(GL3W_INCLUDE_DIR "${GL3W_INCLUDE_DIR}" PARENT_SCOPE)
