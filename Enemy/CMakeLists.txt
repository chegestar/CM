include_directories(../Extras)
include_directories(..)
include_directories(.)

set (ENEMY_SRC
  Enemy.cpp
  Spider.cpp
)

add_library(enemy ${ENEMY_SRC})