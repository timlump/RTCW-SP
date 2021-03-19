cmake_minimum_required(VERSION 3.2)
project (splines)

add_definitions(
-D_LIB
-D_CRT_SECURE_NO_WARNINGS
)

set(HEADER_FILES
math_angles.h
math_matrix.h
math_quaternion.h
math_vector.h
../game/q_shared.h
q_splineshared.h
splines.h
util_list.h
util_str.h
)

set(SOURCE_FILES
math_angles.cpp
math_matrix.cpp
math_quaternion.cpp
math_vector.cpp
q_parse.cpp
q_shared.cpp
splines.cpp
util_str.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})