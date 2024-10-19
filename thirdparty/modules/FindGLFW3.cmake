# Locate the glfw3 library
#
# This module defines the following variables:
#
# GLFW3_LIBRARY the name of the library;
# GLFW3_INCLUDE_DIR where to find glfw include files.
# GLFW3_FOUND true if both the GLFW3_LIBRARY and GLFW3_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called GLFW3_ROOT which points to the root of the glfw library
# installation.
#
# default search dirs
# 
# Cmake file from: https://github.com/daw42/glslcookbook


# Clear the variable so the most recent path is always validated and reported.
unset(_LIBRARY)
unset(_INCLUDE)
unset(GLFW3_LIBRARY_DIR)
unset(GLFW3_INCLUDE_DIR)


# Check environment for root search directory
set( _glfw3_ENV_ROOT $ENV{GLFW3_ROOT} )
if( NOT GLFW3_ROOT AND _glfw3_ENV_ROOT )
	set(GLFW3_ROOT ${_glfw3_ENV_ROOT} )
endif()


# Put user specified location at beginning of search
if(GLFW3_ROOT)
	set(_INCLUDE "${GLFW3_ROOT}/include")
	set(_LIBRARY "${GLFW3_ROOT}/lib-vc2022")
endif()

FIND_PATH(GLFW3_INCLUDE_DIR NAMES "GLFW/glfw3.h" PATHS ${_INCLUDE})
FIND_LIBRARY(GLFW3_LIBRARY_DIR NAMES glfw3 glfw PATHS ${_LIBRARY} )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW3 DEFAULT_MSG GLFW3_LIBRARY_DIR GLFW3_INCLUDE_DIR)


add_library(GLFW3 STATIC IMPORTED)
set_target_properties(GLFW3 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GLFW3 INTERFACE ${GLFW3_INCLUDE_DIR})
set_target_properties(GLFW3 PROPERTIES IMPORTED_LOCATION ${GLFW3_LIBRARY_DIR})