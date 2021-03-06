IF(WIN32) 
	# platform defines for Windows 32bit Systems
	# define math constants like M_PI on Windows
	ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
ELSEIF(APPLE) 
	# platform defines for Mac OS X Systems
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		ADD_DEFINITIONS(-DPOSIX -DAPPLE -D__APPLE__)
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ELSE(WIN32)	
	# assumes linux/UNIX # platform defines for Linux Systems
	ADD_DEFINITIONS(-DPOSIX -DLINUX -D__LINUX__)
ENDIF(WIN32)
ADD_DEFINITIONS( -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE )
#define the architecture
IF( ${CMAKE_BUILD_TYPE} STREQUAL "ATOM" )
 ADD_DEFINITIONS(-D ARCH_x86)
ELSE()
	IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR APPLE )
	 ADD_DEFINITIONS(-D ARCH_x86_64)
	ELSE()
	 ADD_DEFINITIONS(-D ARCH_x86)
	ENDIF() 
ENDIF()

# add global definitions (all platforms, all compilers, all sources)
ADD_DEFINITIONS(-DNOMINMAX)

SET( CVT_DATA_FOLDER "${CMAKE_SOURCE_DIR}/data" )
ADD_DEFINITIONS(-DCVT_DATA_FOLDER="${CVT_DATA_FOLDER}" -D__STDC_CONSTANT_MACROS)
