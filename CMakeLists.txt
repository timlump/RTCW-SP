cmake_minimum_required(VERSION 3.2)
project (rtcw)

add_definitions(
-D_USE_ANGLE
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  $<1:D:/RTCW>)

add_subdirectory(src/botlib)
add_subdirectory(src/cgame)
add_subdirectory(src/extractfuncs)
add_subdirectory(src/game)
add_subdirectory(src/ui)
add_subdirectory(src/renderer)
add_subdirectory(src/splines)
add_subdirectory(src)