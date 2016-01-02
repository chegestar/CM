

set (SWITCH_SRC
  Switch.cpp
  Web.cpp
  FakeExit.cpp
  Trigger.cpp
  Hint.cpp
)

set (COLLECTABLE_SRC
  Collectable.cpp
  Crystal.cpp
  Coin.cpp
  EpCrystal.cpp
  Life.cpp
  Item.cpp
  FireBoot.cpp
  Dynamite.cpp
)

add_library(collect ${SWITCH_SRC} ${COLLECTABLE_SRC})