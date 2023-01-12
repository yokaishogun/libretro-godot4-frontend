#pragma once

#include <libretro.h>

bool core_load(const char *sofile);
bool core_load_game(const char *filename);
void core_unload();
void core_get_system_info(struct retro_system_info *system);
void core_get_system_av_info(struct retro_system_av_info *av);
void core_run();
bool is_initialized();
