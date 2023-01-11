//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef GDRETRO_CLASS_H
#define GDRETRO_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "libretro.h"

using namespace godot;

struct retro_core {
  void *handle;
  bool initialized;
  bool supports_no_game;
  // The last performance counter registered. TODO: Make it a linked list.
  struct retro_perf_counter* perf_counter_last;

  void (*retro_init)(void);
  void (*retro_deinit)(void);
  unsigned (*retro_api_version)(void);
  void (*retro_get_system_info)(struct retro_system_info *info);
  void (*retro_get_system_av_info)(struct retro_system_av_info *info);
  void (*retro_set_controller_port_device)(unsigned port, unsigned device);
  void (*retro_reset)(void);
  void (*retro_run)(void);
  // size_t retro_serialize_size(void);
  // bool retro_serialize(void *data, size_t size);
  // bool retro_unserialize(const void *data, size_t size);
  // void retro_cheat_reset(void);
  // void retro_cheat_set(unsigned index, bool enabled, const char *code);
  bool (*retro_load_game)(const struct retro_game_info *game);
  // bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info);
  void (*retro_unload_game)(void);
  // unsigned retro_get_region(void);
  // void *retro_get_memory_data(unsigned id);
  // size_t retro_get_memory_size(unsigned id);
};

class GDRetro : public Node {
  GDCLASS(GDRetro, Node);
  
  protected:
    
    // TODO SDL_Window *g_win = NULL;
    // TODO SDL_GLContext *g_ctx = NULL;
    // TODO SDL_AudioDeviceID g_pcm = 0;
    retro_frame_time_callback runloop_frame_time;
    retro_usec_t runloop_frame_time_last = 0;
    const uint8_t *g_kbd = NULL;
    retro_audio_callback audio_callback;
    float g_scale = 3;
    bool running = true;
    // TODO g_video
    // TODO g_shader
    retro_variable *g_vars = NULL;
    retro_core *g_retro = NULL;
    
    static void _bind_methods();

  public:
    GDRetro();
    ~GDRetro();
    
    void _ready() override;
	  void _process(double delta) override;
    
    void core_log(enum retro_log_level level, const char *fmt, ...);
    bool core_environment(unsigned cmd, void *data);
    void core_load(String p_sofile);
    void core_load_game(String p_filename);
    void core_unload();
    bool bind_is_initialized();
    unsigned bind_retro_api_version();
    Variant bind_retro_get_system_info();
    Variant bind_retro_get_system_av_info();
    void bind_retro_set_controller_port_device(unsigned port, unsigned device);
    void bind_retro_reset();
    void bind_retro_run();
    void bind_retro_unload_game();
};

#endif // GDRETRO_CLASS_H
