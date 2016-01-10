cmake_minimum_required (VERSION 2.6)
project (CM)
option(ENABLE_DEBUG "ENABLE_DEBUG" OFF)
option(ENABLE_PREVERSION "ENABLE_PREVERSION" OFF)
IF(ENABLE_PREVERSION)
  add_definitions(-DPREVERSION)
ENDIF()
IF(ENABLE_DEBUG)
  add_definitions(-DCOMPILE_DEBUG)
ENDIF()
add_definitions(-DCOMPILE_NO_VB)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SFML COMPONENTS system window graphics audio)

file(COPY Fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY graphics DESTINATION ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(Blocks)
include_directories(Enemy)
include_directories(Exits)
include_directories(Boss1)
include_directories(Extras)
include_directories(Switches)
include_directories(Collectables)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
else()
  message("[ERROR] Didn't find SFML")
endif()

add_subdirectory(Blocks)
add_subdirectory(Extras)
add_subdirectory(Enemy)
add_subdirectory(Exits)
add_subdirectory(Boss1)
add_subdirectory(Switches)
add_subdirectory(Collectables)
add_subdirectory(levels)


set(ROOT_SOURCES
   Main.cpp
   Codes.cpp
   Actor.cpp
   Mover.cpp
   Bob.cpp
   Level.cpp
   SpeechBubble.cpp
)


add_executable(CM ${ROOT_SOURCES})

target_link_libraries(CM extras)
target_link_libraries(CM exits)
target_link_libraries(CM blocks)
target_link_libraries(CM boss1)
target_link_libraries(CM collect)
target_link_libraries(CM enemy)
target_link_libraries(CM switch)



if (SFML_FOUND)
  target_link_libraries(CM ${SFML_LIBRARIES})
endif()

