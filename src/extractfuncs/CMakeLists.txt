cmake_minimum_required(VERSION 3.2)
project (extractfuncs)

add_definitions(
-D_CONSOLE
-DSCREWUP
-D_CRT_SECURE_NO_WARNINGS)

set(HEADER_FILES
../botlib/be_interface.h
../game/botlib.h
../bspc/l_bsp_ent.h
../bspc/l_bsp_q2.h
../bspc/l_cmd.h
../bspc/l_log.h
l_log.h
../bspc/l_math.h
../bspc/l_mem.h
l_memory.h
../bspc/l_poly.h
l_precomp.h
../bspc/l_qfiles.h
l_script.h
../botlib/l_script.h
../bspc/l_threads.h
../bspc/l_utils.h
../bspc/q2files.h
../game/q_shared.h
../bspc/qbsp.h
../bspc/qfiles.h
../game/surfaceflags.h
../qcommon/unzip.h
)

set(SOURCE_FILES
extractfuncs.c
l_log.c
l_memory.c
l_precomp.c
l_script.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})