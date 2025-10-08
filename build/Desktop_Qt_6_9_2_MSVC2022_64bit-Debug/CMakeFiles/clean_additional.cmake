# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Biblioteca_autogen"
  "CMakeFiles\\Biblioteca_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Biblioteca_autogen.dir\\ParseCache.txt"
  )
endif()
