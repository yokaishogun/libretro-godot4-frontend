#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

/*class GDRetro : public CanvasItem {
  GDCLASS(GDRetro, CanvasItem);*/
class GDRetro : public Node2D {
  GDCLASS(GDRetro, Node2D);
  
  bool centered = true;
  Point2 offset;
  bool hflip = false;
  bool vflip = false;
  
  Ref<Texture2D> texture;
  void _texture_changed();
  void _get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip_enabled) const;
  
  protected:
    void _notification(int p_what);
    static void _bind_methods();
  
  public:
    GDRetro();
    ~GDRetro();
    void _ready() override;
	  void _process(double delta) override;
    bool _core_load(String sofile);
    bool _core_load_game(String filename);
    void _core_unload();
    Variant _core_get_system_info();
    Variant _core_get_system_av_info();
    void _core_run();
    bool _is_initialized();
    
    void set_texture(const Ref<Texture2D> &p_texture);
	  Ref<Texture2D> get_texture() const;
};
