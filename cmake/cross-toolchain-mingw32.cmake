# Target operating system and architecture
set( CMAKE_SYSTEM_NAME Windows )
set( CMAKE_SYSTEM_PROCESSOR x86 )

# C/C++ compilers
set( CMAKE_C_COMPILER i686-w64-mingw32-gcc )
set( CMAKE_CXX_COMPILER i686-w64-mingw32-g++ )
set( CMAKE_RC_COMPILER i686-w64-mingw32-windres )

# Target prefix
set( CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32 )

# Find programs using host paths and headers/libraries using target paths
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
