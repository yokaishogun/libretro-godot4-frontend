extends Node

func _ready():
  $ui_canvas_layer/ui/label.text = get_status()

func _on_button_core_pressed():
  if $gd_retro.is_initialized():
    $gd_retro.core_unload()
    $ui_canvas_layer/ui/label.text = get_status()
  else:
    $file_dialog_core.popup()

func _on_button_game_pressed():
  if not $gd_retro.is_initialized(): return
  $file_dialog_game.popup()

func _on_file_dialog_core_file_selected(path):
  $gd_retro.core_load(path)
  $ui_canvas_layer/ui/label.text = get_status()

func _on_file_dialog_game_file_selected(path):
  pass

func get_status():
  print($gd_retro.retro_get_system_info())
  print($gd_retro.retro_get_system_av_info())
  var text = "GDRetro\n"
  if $gd_retro.is_initialized():
    var status = $gd_retro.retro_get_system_info()
    text += "Core loaded.\n%s %s" % [status["library_name"], status["library_version"]]
    $ui_canvas_layer/ui/buttons_container/button_core.text = "UNLOAD CORE"
    $ui_canvas_layer/ui/buttons_container/button_game.disabled = false
  else:
    text += "No core loaded."
    $ui_canvas_layer/ui/buttons_container/button_core.text = "LOAD CORE"
    $ui_canvas_layer/ui/buttons_container/button_game.disabled = true
  return text
