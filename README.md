# Raspberry PICO Infrared Receiver

This library enables you to read Infrared signals with the RP2040 MCU

### Features
* NEC Protocol   ([more information](https://www.sbprojects.net/knowledge/ir/nec.php))

## Usage

To use the compiled library you have 2 options

### Using the `.a` file

This uses a fixed version

1. Download the latest precompiled `libinfrared.a` from github releases
2. Place it inside a `libs` folder in your project
3. use `find_library(infrared infrared libs)`
   1. `libs` must be the name of the folder containing the `a` file
4. Use `infrared` in `target_link_libraries(...)`

### Sourcecode inclusion

This version can easily be changed with `git checkout <version>`

1. Clone the repo
2. Add `add_subdirectory(/path/to/my/lib)` (the path can also be relative)
3. Use `infrared` in `link_target_link_libraries(...)`



## Commands

| Command | Description |
|:--------|:------------|
| `compile.sh` | compiles the library and the example |
|`flash.sh` | compiles & flashes the example to the pico using *picotool* |
| `rebuild.sh` | builds the project from ground up (can fix some cmake weirdos sometimes) |

## Example

[CMAKE](example/CMakeLists.txt) (This is only minimal! but shows the lib inclusion)<br>
[Source](example/main.cpp)