# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\mazeGenerator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\mazeGenerator_autogen.dir\\ParseCache.txt"
  "mazeGenerator_autogen"
  )
endif()
