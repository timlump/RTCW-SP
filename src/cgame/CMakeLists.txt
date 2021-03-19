cmake_minimum_required(VERSION 3.2)
project (cgame)

add_definitions(
-DCGAMEDLL
-D_CRT_SECURE_NO_WARNINGS)

set(HEADER_FILES
../game/bg_local.h
../game/bg_public.h
cg_local.h
cg_public.h
../ui/keycodes.h
../../main/ui/menudef.h
../game/q_shared.h
../game/surfaceflags.h
tr_types.h
../ui/ui_shared.h
)

set(SOURCE_FILES
../game/bg_animation.c
../game/bg_lib.c
../game/bg_misc.c
../game/bg_pmove.c
../game/bg_slidemove.c
cg_consolecmds.c
cg_draw.c
cg_drawtools.c
cg_effects.c
cg_ents.c
cg_event.c
cg_flamethrower.c
cg_info.c
cg_localents.c
cg_main.c
cg_marks.c
cg_newDraw.c
cg_particles.c
cg_players.c
cg_playerstate.c
cg_predict.c
cg_scoreboard.c
cg_servercmds.c
cg_snapshot.c
cg_sound.c
cg_syscalls.c
cg_trails.c
cg_view.c
cg_weapons.c
../game/q_math.c
../game/q_shared.c
../ui/ui_shared.c
cgame.def
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>)