cmake_minimum_required(VERSION 3.1)
project("TechSupportRL")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/SFML-2.4.1/cmake/Modules)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wpedantic -march=native -mtune=native -g")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -L/opt/local/lib -L/usr/lib/i386-linux-gnu")

add_library(rltk 	src/external/rltk/rltk/rltk.cpp
					src/external/rltk/rltk/texture_resources.cpp
					src/external/rltk/rltk/color_t.cpp
					src/external/rltk/rltk/virtual_terminal.cpp
					src/external/rltk/rltk/rng.cpp
					src/external/rltk/rltk/geometry.cpp
					src/external/rltk/rltk/input_handler.cpp
					src/external/rltk/rltk/font_manager.cpp
					src/external/rltk/rltk/gui.cpp
					src/external/rltk/rltk/layer_t.cpp
					src/external/rltk/rltk/gui_control_t.cpp
					src/external/rltk/rltk/virtual_terminal_sparse.cpp
					src/external/rltk/rltk/ecs.cpp
					src/external/rltk/rltk/xml.cpp
					src/external/rltk/rltk/perlin_noise.cpp
					src/external/rltk/rltk/rexspeeder.cpp
)

# Require SFML
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Add all of the example executables and their library dependency
include_directories(src/external/rltk/rltk)
add_executable(tsrl src/main.cpp 
	src/mode_stack/menu_mode.cpp
	src/mode_stack/intro_mode.cpp
	src/mode_stack/game_mode.cpp
	src/mode_stack/dead_mode.cpp
	src/mode_stack/win_mode.cpp
	src/globals.cpp
	src/systems/render_system.cpp
	src/systems/keyboard_system.cpp
	src/systems/hud_system.cpp
	src/systems/movement_system.cpp
	src/systems/caffeine_system.cpp
	src/systems/time_system.cpp
	src/systems/visibility_system.cpp
	src/systems/blocking_system.cpp
	src/systems/ai_system.cpp
	src/systems/log_system.cpp
	src/systems/despair_system.cpp
	src/components/logger.cpp
	src/mode_stack/tablet_mode.cpp
	src/mode_stack/tablet_mode.hpp
	src/systems/mission_system.cpp
	src/systems/path_finding.cpp)
target_link_libraries(rltk ${SFML_LIBRARIES})
target_link_libraries(tsrl rltk)

if (APPLE)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
    set(MACOSX_BUNDLE_COPYRIGHT "Copyright 2015-Present Bracket Productions")
    set(MACOSX_BUNDLE_BUNDLE_NAME "Tech Support - The Roguelike")
    set(MACOSX_BUNDLE_ICON_FILE "icon")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0")
#    set(myApp_ICON ${CMAKE_CURRENT_SOURCE_DIR}/../assets/icon.icns)
 #   set_source_files_properties(${myApp_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(techsupportrl MACOSX_BUNDLE src/main.cpp
            src/mode_stack/menu_mode.cpp
            src/mode_stack/intro_mode.cpp
            src/mode_stack/game_mode.cpp
            src/mode_stack/dead_mode.cpp
            src/mode_stack/win_mode.cpp
            src/globals.cpp
            src/systems/render_system.cpp
            src/systems/keyboard_system.cpp
            src/systems/hud_system.cpp
            src/systems/movement_system.cpp
            src/systems/caffeine_system.cpp
            src/systems/time_system.cpp
            src/systems/visibility_system.cpp
            src/systems/blocking_system.cpp
            src/systems/ai_system.cpp
            src/systems/log_system.cpp
            src/systems/despair_system.cpp
            src/components/logger.cpp
            src/mode_stack/tablet_mode.cpp
            src/mode_stack/tablet_mode.hpp
            src/systems/mission_system.cpp
            src/systems/path_finding.cpp)
    target_link_libraries(techsupportrl rltk)
    install(CODE "
	include (BundleUtilities)
	fixup_bundle(${CMAKE_INSTALL_PREFIX}/techsupportrl.app \"\" \"\")
	" COMPONENT techsupportrl)
    add_custom_command(
            TARGET techsupportrl
            COMMAND mkdir -p techsupportrl.app/Contents/MacOS/assets
            COMMAND cp ../assets/* techsupportrl.app/Contents/MacOS/assets/
    )
endif()

# Require Boost
set(Boost_USE_STATIC_LIBS      OFF) # only find static libs
set(Boost_USE_MULTITHREADED    ON)
set(Boost_USE_STATIC_RUNTIME   OFF)
find_package(Boost COMPONENTS filesystem system REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(rltk ${Boost_LIBRARIES})
endif()

# We depend upon zlib
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
	include_directories(${ZLIB_INCLUDE_DIRS})
	target_link_libraries(rltk ${ZLIB_LIBRARIES})
endif()
