# 源文件
SRC = ./source/stage.c
DST = ./windows/stage.exe
# SDL 库的位置
SDLDIR = ./library/SDL2-devel-2.0.14-mingw/SDL2-2.0.14/x86_64-w64-mingw32
# 依赖参数
LFLAGS = -I $(SDLDIR)/include -L $(SDLDIR)/lib
# 编译参数
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -O2 # -mwindows
# 选择编译器
CC = gcc

SRC_CONFIG = ./config.txt
DST_CONFIG = ./windows/config.txt

SRC_DSL_DLL = $(SDLDIR)/bin/SDL2.dll
DST_DSL_DLL = ./windows/SDL2.dll

# $(info MESSAGE)
# $(warning MESSAGE)
# $(error MESSAGE)

run: $(SRC)
	@$(CC) $(SRC) $(LFLAGS) $(CFLAGS) -o $(DST)
	@cp $(SRC_CONFIG) $(DST_CONFIG)
	@cp $(SRC_DSL_DLL) $(DST_DSL_DLL)
	@./$(DST)
