//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef GDRETRO_CLASS_H
#define GDRETRO_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class GDRetro : public RefCounted {
  GDCLASS(GDRetro, RefCounted);
  
  protected:
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
    
    static void _bind_methods();

  public:
    GDRetro();
    ~GDRetro();
    
    void core_load(String p_sofile);
    void core_unload();
    unsigned bind_retro_api_version();
    Dictionary bind_retro_get_system_info();
    Dictionary bind_retro_get_system_av_info();
    bool bind_is_initialized();
};

#endif // GDRETRO_CLASS_H
