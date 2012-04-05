FIND_PATH(OPENNI_INCLUDES 
	NAMES XnOpenNI.h
	PATHS
	${CMAKE_INCLUDE_PATH}
	/usr/local/dc1394/include/ni
	/usr/local/include/ni
	/usr/include/ni
	/opt/local/include/ni
)

FIND_LIBRARY(OPENNI_LIBRARY
	NAMES OpenNI
	PATHS
	${CMAKE_LIBRARY_PATH}
	/usr/local/dc1394/lib
	/usr/local/lib
	/usr/lib
	/opt/local/lib
)

IF( OPENNI_LIBRARY AND OPENNI_INCLUDES )
	FIND_LIBRARY( OPENNI_PRIME_SENSOR_MODULE 
		NAMES XnCore
		PATHS
		${CMAKE_LIBRARY_PATH}
		/usr/local/dc1394/lib
		/usr/local/lib
		/usr/lib
		/opt/local/lib
	)

	SET( OPENNI_FOUND TRUE)
	ADD_DEFINITIONS( -DOPENNI_FOUND )

	SET( OPENNI_LIBRARIES
		${OPENNI_LIBRARY}
		${OPENNI_PRIME_SENSOR_MODULE}
	)
ENDIF()

MARK_AS_ADVANCED(
	OPENNI_INCLUDES
	OPENNI_LIBRARY
) 