appbindir  = ${prefix}/games/xcomeu3d/bin

appbin_PROGRAMS = xcomeu3d

neoapplication_SOURCES = main.cpp application.cpp error.cpp systeminput.cpp

EXTRA_DIST = base.h application.h error.h systeminput.h

# set the include path found by configure
INCLUDES= $(all_includes)
 
# the library search path.
xcomeu3d_LDFLAGS = $(all_libraries)
