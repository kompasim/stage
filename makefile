# 源文件
DST_NAME = stage.exe
SRC = ./source/stage.c
DST = ./windows/$(DST_NAME)
# SDL 库的位置
SDL_DIR = ./library/SDL2-devel-2.0.14-mingw/SDL2-2.0.14/x86_64-w64-mingw32
SDL_IMG_DIR = ./library/SDL2_image-devel-2.0.5-mingw/SDL2_image-2.0.5/x86_64-w64-mingw32
SDL_TTF_DIR = ./library/SDL2_ttf-devel-2.0.15-mingw/SDL2_ttf-2.0.15/x86_64-w64-mingw32
# 依赖参数
SDL_FLAGS = -I $(SDL_DIR)/include/SDL2 -L $(SDL_DIR)/lib
SDL_IMG_FLAGS = -I $(SDL_IMG_DIR)/include/SDL2 -L $(SDL_IMG_DIR)/lib
SDL_TTF_FLAGS = -I $(SDL_TTF_DIR)/include/SDL2 -L $(SDL_TTF_DIR)/lib
# 编译参数
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -O2 # -mwindows
# 选择编译器
CC = gcc

SRC_OTHERS = ./others/*
DST_WINDOWS = ./windows/

SRC_DSL_DLL = $(SDL_DIR)/bin/SDL2.dll
SRC_DSL_IMG_DLL = $(SDL_IMG_DIR)/bin/SDL2_image.dll
SRC_DSL_TTF_DLL = $(SDL_TTF_DIR)/bin/SDL2_ttf.dll

# $(info MESSAGE)
# $(warning MESSAGE)
# $(error MESSAGE)

run: $(SRC)
	@rm -rf $(DST_WINDOWS)*
	@$(CC) $(SRC) $(SDL_FLAGS) $(SDL_IMG_FLAGS) $(SDL_TTF_FLAGS) $(CFLAGS) -o $(DST)
	@cp -ri $(SRC_OTHERS) $(DST_WINDOWS)
	@cp $(SRC_DSL_DLL) $(DST_WINDOWS)
	@cp $(SRC_DSL_IMG_DLL) $(DST_WINDOWS)
	@cp $(SRC_DSL_TTF_DLL) $(DST_WINDOWS)
	@cd $(DST_WINDOWS)
	@cd ./windows/ && ./$(DST_NAME)
