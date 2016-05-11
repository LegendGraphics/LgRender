CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )

PROJECT ( LgRender )

ENABLE_TESTING()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

IF(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")
  ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion-null")
  ENDIF()
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

  FIND_PROGRAM(XIAR xiar)
  IF(XIAR)
    SET(CMAKE_AR "${XIAR}")
  ENDIF(XIAR)
  MARK_AS_ADVANCED(XIAR)

  FIND_PROGRAM(XILD xild)
  IF(XILD)
    SET(CMAKE_LINKER "${XILD}")
  ENDIF(XILD)
  MARK_AS_ADVANCED(XILD)

ENDIF()

IF(MSVC)
  ADD_DEFINITIONS (/D _CRT_SECURE_NO_WARNINGS)
  ADD_DEFINITIONS (/D YY_NO_UNISTD_H)
ENDIF()

FIND_PACKAGE ( Threads )

IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
  ADD_DEFINITIONS (-DNDEBUG)
ENDIF()

 

INCLUDE_DIRECTORIES ( ${CMAKE_SOURCE_DIR} )
  
FILE( GLOB core 			  "lgrender/core/*.*" ) 
FILE( GLOB math 			  "lgrender/math/*.*" )  
FILE( GLOB shapes 			  "lgrender/shapes/*.*" ) 
					 
source_group("core" 			FILES ${core} )
source_group("math" 			FILES ${math} )
source_group("shapes" 			FILES ${shapes} )


ADD_LIBRARY ( lgrender STATIC
  ${core}
  ${math}
  ${shapes}
  )

IF (WIN32)
  # Avoid a name clash when building on Visual Studio
  SET_TARGET_PROPERTIES ( lgrender
    PROPERTIES
    OUTPUT_NAME libpbrt
    )
ENDIF()

FIND_PACKAGE ( Threads )

# Main renderer
ADD_EXECUTABLE ( lgrender_exe
  lgrender/main/lgrender.cpp
  )

SET_TARGET_PROPERTIES ( lgrender_exe
  PROPERTIES
  OUTPUT_NAME lgrender
  )

TARGET_LINK_LIBRARIES ( lgrender_exe
  lgrender
  ${CMAKE_THREAD_LIBS_INIT}
  )


# Installation

INSTALL ( TARGETS
  lgrender_exe
  DESTINATION
  bin
  )

INSTALL ( TARGETS
  lgrender
  DESTINATION
  lib
  )
  
  
  
