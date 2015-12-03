include_directories(..)
include_directories(Extras)

set(PLATFORM_SRC
  Block.cpp
  GemDoor.cpp
)

add_library(blocks ${PLATFORM_SRC})

