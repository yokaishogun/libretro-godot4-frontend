# libretro-godot4-frontend

A GDExtension for libretro API to allow core loading in Godot 4.

**Work in progress.**

## Using the extension
After compiling the extension succesfully, you can now use the libretro API inside Godot
```gdscript
@onready var gdretro = GDRetro.new()

func _ready() -> void:
	gdretro.core_load("/usr/lib/libretro/gambatte_libretro.so")
	var system_info = gdretro.retro_get_system_info()
	print(system_info["library_name"])
	print(system_info["library_version"])
```

## Versioning
This repository will be updated regularly to work with the latest beta release of the master (4.0) branch. If you can't compile the extension, please open an issue.

----> **Most Recent Update: Godot 4 Beta 10 working**

## Contributing
If you can't compile the extension, please open an issue with the error log in your terminal and/or the error log in the editor (if you can't run the example scene).

PRs for improvements are very welcome!

## Building the extension

To compile the extension you need to follow these steps:

1. Clone the extension recursively from this repository
```bash
# --recursive to automatically load the submodule godot-cpp
# The git adress can be found under the green "Code" dropdown menu
git clone --recursive <github-repo-url>
```
2. Go inside the repo fodler folder
```bash
cd libretro-godot4-frontend
```

3. Make sure you are on the right commit of the godot-cpp repository
```bash
git status
# this show's you the commit. Make sure that it is released to a similar/the same time as the master branch (especially during the beta)
```
To make sure you have the right commit, here the [link to the pinned updated issue with the commit hashes](https://github.com/godotengine/godot-cpp/issues/874)

4. Go inside the godot-cpp folder
```bash
cd godot-cpp
```

5. Compile godot-cpp and generate the bindings (only needed once when starting development or when there is an update of the submodule)
```bash
scons target=template_debug
# OR simpler (the above is the default configuration):
scons 
```

6. Go back to the top level of the directory
```bash
cd ..
```

7. Compile the extension
```bash
scons target=template_debug
# OR simpler (the above is the default configuration):
scons
```
