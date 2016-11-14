cmake_minimum_required(VERSION 3.1)
project("TechSupportRL")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/src/external/rltk/cmake_modules)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wpedantic -march=native -mtune=native -g")
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
add_executable(tsrl src/main.cpp)
target_link_libraries(rltk ${SFML_LIBRARIES})
target_link_libraries(tsrl rltk)

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