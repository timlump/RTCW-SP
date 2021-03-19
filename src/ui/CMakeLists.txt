cmake_minimum_required(VERSION 3.2)
project (ui)

add_definitions(
-D_USRDLL
-DUI_EXPORTS
-D_CRT_SECURE_NO_WARNINGS
)

set(HEADER_FILES
../game/bg_public.h
keycodes.h
../../main/ui/menudef.h
../game/q_shared.h
../game/surfaceflags.h
../cgame/tr_types.h
ui_local.h
ui_public.h
ui_shared.h
)

set(SOURCE_FILES
../game/bg_lib.c
../game/bg_misc.c
../game/q_math.c
../game/q_shared.c
ui_atoms.c
ui_gameinfo.c
ui_main.c
ui_players.c
ui_shared.c
ui_syscalls.c
ui_util.c
ui.def
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>)
target_link_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/LARGEADDRESSAWARE:NO>)