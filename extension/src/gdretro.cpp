//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "libretro.h"
#include "gdretro.h"

using namespace godot;

#define load_sym(H, V, S) do { \
  if (!((*(void**)&V) = dlsym(H, #S))) { \
    fprintf(stdout, "failed to load symbol '" #S "'': %s", dlerror()); \
    exit(1); \
  } \
} while (0)

void *load_dynamic_object(const char *sofile) {
  char *error;
  void *handle = dlopen(sofile, RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }
  dlerror();
  return handle;
}

GDRetro::GDRetro() {
  
}

GDRetro::~GDRetro() {
  core_unload();
}

void GDRetro::core_load(String p_sofile) {
  extern void retro_init(void);
  extern void retro_deinit(void);
  extern unsigned int retro_api_version(void);
  extern void retro_get_system_info(struct retro_system_info *info);
  extern void retro_get_system_av_info(struct retro_system_av_info *info);
  extern void retro_set_controller_port_device(unsigned port, unsigned device);
  extern void retro_reset(void);
  extern void retro_run(void);
  extern bool retro_load_game(const struct retro_game_info *game);
  extern void retro_unload_game(void);
  
  void (*set_environment)(retro_environment_t) = NULL;
  void (*set_video_refresh)(retro_video_refresh_t) = NULL;
  void (*set_input_poll)(retro_input_poll_t) = NULL;
  void (*set_input_state)(retro_input_state_t) = NULL;
  void (*set_audio_sample)(retro_audio_sample_t) = NULL;
  void (*set_audio_sample_batch)(retro_audio_sample_batch_t) = NULL;
  
  handle = load_dynamic_object(p_sofile.utf8().get_data());
  
  load_sym(handle, (*this).retro_init, retro_init);
  load_sym(handle, (*this).retro_deinit, retro_deinit);
  load_sym(handle, (*this).retro_api_version, retro_api_version);
  load_sym(handle, (*this).retro_get_system_info, retro_get_system_info);
  load_sym(handle, (*this).retro_get_system_av_info, retro_get_system_av_info);
  load_sym(handle, (*this).retro_set_controller_port_device, retro_set_controller_port_device);
  load_sym(handle, (*this).retro_reset, retro_reset);
  load_sym(handle, (*this).retro_run, retro_run);
  load_sym(handle, (*this).retro_load_game, retro_load_game);
  load_sym(handle, (*this).retro_unload_game, retro_unload_game);
  
  load_sym(handle, set_environment, retro_set_environment);
  load_sym(handle, set_video_refresh, retro_set_video_refresh);
  load_sym(handle, set_input_poll, retro_set_input_poll);
  load_sym(handle, set_input_state, retro_set_input_state);
  load_sym(handle, set_audio_sample, retro_set_audio_sample);
  load_sym(handle, set_audio_sample_batch, retro_set_audio_sample_batch);
  
  /*set_environment(core_environment);
  set_video_refresh(core_video_refresh);
  set_input_poll(core_input_poll);
  set_input_state(core_input_state);
  set_audio_sample(core_audio_sample);
  set_audio_sample_batch(core_audio_sample_batch);
  
  (*this).retro_init();*/
  initialized = true;
  
  retro_system_info system_info;
  (*this).retro_get_system_info(&system_info);
  
  char print_string[128];
  snprintf(print_string, 128, "gdretro: core loaded %s %s",
    system_info.library_name,
    system_info.library_version
  );
  UtilityFunctions::print(print_string);
}

void GDRetro::core_unload() {
  dlclose(handle);
}

unsigned GDRetro::bind_retro_api_version() {
  return retro_api_version();
}

bool GDRetro::bind_is_initialized() {
  return initialized;
}

Dictionary GDRetro::bind_retro_get_system_info() {
  retro_system_info system_info;
  (*this).retro_get_system_info(&system_info);
  
  Dictionary system_info_dict = Dictionary();
  system_info_dict["library_name"] = system_info.library_name;
  system_info_dict["library_version"] = system_info.library_version;
  system_info_dict["need_fullpath"] = system_info.need_fullpath;
  system_info_dict["block_extract"] = system_info.block_extract;
  
  return system_info_dict;
}

Dictionary GDRetro::bind_retro_get_system_av_info() {
  retro_system_av_info system_av_info;
  (*this).retro_get_system_av_info(&system_av_info);
  
  Dictionary system_av_info_geometry_dict = Dictionary();
  system_av_info_geometry_dict["aspect_ratio"] = system_av_info.geometry.aspect_ratio;
  system_av_info_geometry_dict["base_height"] = system_av_info.geometry.base_height;
  system_av_info_geometry_dict["base_width"] = system_av_info.geometry.base_width;
  system_av_info_geometry_dict["max_height"] = system_av_info.geometry.max_height;
  system_av_info_geometry_dict["max_width"] = system_av_info.geometry.max_width;
  
  Dictionary system_av_info_timing_dict = Dictionary();
  system_av_info_timing_dict["fps"] = system_av_info.timing.fps;
  system_av_info_timing_dict["sample_rate"] = system_av_info.timing.sample_rate;
  
  Dictionary system_av_info_dict = Dictionary();
  system_av_info_dict["geometry"] = system_av_info_geometry_dict;
  system_av_info_dict["timing"] = system_av_info_timing_dict;
  
  return system_av_info_dict;
}

void GDRetro::_bind_methods() {
  ClassDB::bind_method(D_METHOD("core_load"), &GDRetro::core_load);
  ClassDB::bind_method(D_METHOD("core_unload"), &GDRetro::core_unload);
  ClassDB::bind_method(D_METHOD("retro_api_version"), &GDRetro::bind_retro_api_version);
  ClassDB::bind_method(D_METHOD("retro_get_system_info"), &GDRetro::bind_retro_get_system_info);
  ClassDB::bind_method(D_METHOD("retro_get_system_av_info"), &GDRetro::bind_retro_get_system_av_info);
  ClassDB::bind_method(D_METHOD("is_initialized"), &GDRetro::bind_is_initialized);
}
