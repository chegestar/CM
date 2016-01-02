include_directories(..)
file(GLOB LEVELS
  "*.txt"
  "*.csv"
)
file(COPY ${LEVELS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)
