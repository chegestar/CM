include_directories(../Extras)
include_directories(..)
include_directories(../Enemies)

set (SWITCH_SRC
)

set (COLLECTABLE_SRC
  Collectable.cpp
)

add_library(collect ${SWITCH_SRC} ${COLLECTABLE_SRC})