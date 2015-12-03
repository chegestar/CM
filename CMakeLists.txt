cmake_minimum_required (VERSION 2.6)
project (CM)
option(ENABLE_SF "ENABLE_DEBUG" OFF)
option(ENABLE_SF "ENABLE_PREVERSION" OFF)
IF(ENABLE_PREVERSION)
  add_definitions(-DPREVERSION)
ENDIF()
IF(ENABLE_DEBUG)
  add_definitions(-DCOMPILE_DEBUG)
ENDIF()
add_definitions(-DCOMPILE_NO_VB)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(Blocks)
include_directories(Enemy)
include_directories(Extras)
include_directories(Collectables)

add_subdirectory(Blocks)
add_subdirectory(Extras)
add_subdirectory(Enemy)
add_subdirectory(Collectables)



set(ROOT_SOURCES
   Main.cpp
   Actor.cpp
   Mover.cpp
   Bob.cpp
   Level.cpp
   CheckPoint.cpp
)

add_executable(CM ${ROOT_SOURCES})

target_link_libraries(CM extras)
target_link_libraries(CM blocks)
target_link_libraries(CM collect)
target_link_libraries(CM enemy)


IF (CYGWIN)
  set(SFML_ROOT E:/)
  MESSAGE(${SFML_ROOT})
ELSE()
  set(SFML_ROOT /home/diamog)
ENDIF()
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SFML REQUIRED system window graphics audio)

if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(CM ${SFML_LIBRARIES})
endif()

