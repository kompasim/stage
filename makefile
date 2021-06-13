
# names
DST_NAME = stage.exe
SRC = ./source/main.c
DST = ./windows/$(DST_NAME)

# locations
SDL_DIR = ./library/SDL2-devel-2.0.14-mingw/SDL2-2.0.14/x86_64-w64-mingw32
SDL_IMG_DIR = ./library/SDL2_image-devel-2.0.5-mingw/SDL2_image-2.0.5/x86_64-w64-mingw32
SDL_TTF_DIR = ./library/SDL2_ttf-devel-2.0.15-mingw/SDL2_ttf-2.0.15/x86_64-w64-mingw32
LUA_DIR = ./library/lua-5.4.3\src

# flags
SDL_FLAGS = -I $(SDL_DIR)/include/SDL2 -L $(SDL_DIR)/lib
SDL_IMG_FLAGS = -I $(SDL_IMG_DIR)/include/SDL2 -L $(SDL_IMG_DIR)/lib
SDL_TTF_FLAGS = -I $(SDL_TTF_DIR)/include/SDL2 -L $(SDL_TTF_DIR)/lib
LUA_FLAGS = -I $(LUA_DIR) -L $(LUA_DIR)

# compile flags
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -llua -O2 # -mwindows
# compiler
CC = gcc

# others
SRC_SCRIPT = ./scripts/*
SRC_OTHERS = ./others/*
DST_WINDOWS = ./windows/

# runtime dynamic libraries
SRC_DSL_DLL = $(SDL_DIR)/bin/SDL2.dll
SRC_DSL_IMG_DLL = $(SDL_IMG_DIR)/bin/SDL2_image.dll
SRC_DSL_TTF_DLL = $(SDL_TTF_DIR)/bin/SDL2_ttf.dll

# $(info MESSAGE)
# $(warning MESSAGE)
# $(error MESSAGE)

# commands
run: $(SRC)
	@rm -rf $(DST_WINDOWS)*
	@$(CC) $(SRC) $(SDL_FLAGS) $(SDL_IMG_FLAGS) $(SDL_TTF_FLAGS) $(LUA_FLAGS) $(CFLAGS) -o $(DST)
	@cp -ri $(SRC_SCRIPT) $(DST_WINDOWS)
	@cp -ri $(SRC_OTHERS) $(DST_WINDOWS)
	@cp $(SRC_DSL_DLL) $(DST_WINDOWS)
	@cp $(SRC_DSL_IMG_DLL) $(DST_WINDOWS)
	@cp $(SRC_DSL_TTF_DLL) $(DST_WINDOWS)
	@cd $(DST_WINDOWS)
	@cd ./windows/ && ./$(DST_NAME)
