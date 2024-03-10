IMGUI_DIR = E:\dev_lib\IMGUI

# OBJS - specifies which files to compile as part of the project
OBJS = Application.cpp JABIWindow.cpp JABIRenderer.cpp JABIGUI.cpp JABIControls.cpp Scene.cpp GameObject.cpp Sprite.cpp Transform.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp $(IMGUI_DIR)/backends/imgui_impl_sdlrenderer2.cpp 

# CC - specifies which compiler
CC = g++

# INCLUDE_PATHS - specifies additional include paths
INCLUDE_PATHS = -IE:\dev_lib\SDL2-2.26.2\i686-w64-mingw32\include\SDL2 -IE:\dev_lib\SDL2_image-2.6.2\i686-w64-mingw32\include\SDL2 -IE:\dev_lib\SDL2_ttf-2.20.1\i686-w64-mingw32\include\SDL2 -IE:\dev_lib\SDL2_mixer-2.6.3\i686-w64-mingw32\include\SDL2 -IE:\dev_lib\IMGUI -IE:\dev_lib\IMGUI\backends

# LIBRARY_PATHS - specifies additional library paths
LIBRARY_PATHS = -LE:\dev_lib\SDL2-2.26.2\i686-w64-mingw32\lib -LE:\dev_lib\SDL2_image-2.6.2\i686-w64-mingw32\lib -LE:\dev_lib\SDL2_ttf-2.20.1\i686-w64-mingw32\lib -LE:\dev_lib\SDL2_mixer-2.6.3\i686-w64-mingw32\lib

# COMPILER_FLAGS - specifies the ad ditional compiltion options
# -w = supresses all warnings
# -Wl,-subsystem,windows = gets rid of console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows -std=c++17

# LINKER_FLAGS - specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# OBJ_NAME - specifies the name of the exe
OBJ_NAME = JADGE_app

# EXE_NAME - name of the output exe
EXE_NAME = JADGE_app.exe

# PROG_PATH - path of folder for output of executable
PROG_PATH = ../bin/

# This is the target that compiles the executable
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	mv $(EXE_NAME) $(PROG_PATH)