extends Node

@onready var gdretro = GDRetro.new()

func _ready():
  set_label_text()

func _on_button_pressed():
  get_node("file_dialog").popup()

func _on_file_dialog_file_selected(path):
  print(path)
  gdretro.core_load(path)
  set_label_text()

func set_label_text():
  if !gdretro.is_initialized():
    get_node("ui_canvas_layer/ui/label").text = "GDRetro\nNo core loaded."
    return
  var system_info = gdretro.retro_get_system_info()
  var system_av_info = gdretro.retro_get_system_av_info()
  get_node("ui_canvas_layer/ui/label").text = "GDRetro:\nCore: %s %s [API v%s]" % [
    system_info["library_name"],
    system_info["library_version"],
    gdretro.retro_api_version()
  ]
  print(system_info)
  print(system_av_info)
