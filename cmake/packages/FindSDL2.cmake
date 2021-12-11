#
# This file is part of C11_TEMPLATE.
#

#
# SDL2_FOUND
# SDL2_INCLUDE_DIR
# SDL2_LIBRARIES
# SDL2_MAIN_LIBRARY
#

find_path(SDL2_INCLUDE_DIR
    NAMES SDL2/SDL.h
    PATHS /usr/include
          /usr/local/include
          "C:/Program Files (x86)/SDL2/include"
          "C:/Program Files/SDL2/include"
)

find_library(SDL2_LIBRARIES
    NAMES SDL2
    PATHS /usr/lib
          /usr/local/lib
          /usr/lib/x86_64-linux-gnu
          "C:/Program Files (x86)/SDL2/lib"
          "C:/Program Files/SDL2/lib"
)

find_library(SDL2_MAIN_LIBRARY
    NAMES SDL2main
    PATHS /usr/lib
          /usr/local/lib
          /usr/lib/x86_64-linux-gnu
          "C:/Program Files (x86)/SDL2/lib"
          "C:/Program Files/SDL2/lib"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2 SDL2_LIBRARIES
    SDL2_MAIN_LIBRARY SDL2_INCLUDE_DIR
)
mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARIES SDL2_MAIN_LIBRARY)
