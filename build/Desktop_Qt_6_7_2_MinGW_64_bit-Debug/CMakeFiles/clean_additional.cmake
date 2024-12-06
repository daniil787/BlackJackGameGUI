# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BlackJack_autogen"
  "CMakeFiles\\BlackJack_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BlackJack_autogen.dir\\ParseCache.txt"
  )
endif()
