

set (SWITCH_SRC
)

set (COLLECTABLE_SRC
  Collectable.cpp
  Crystal.cpp
  Coin.cpp
  EpCrystal.cpp
  Life.cpp
)

add_library(collect ${SWITCH_SRC} ${COLLECTABLE_SRC})