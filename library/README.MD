### install libraries

* SDL2: 
  
> download [SDL2](http://www.libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz) development library to this directory and unzip it.

* SDL2_iamge: 
  
> dwonload [SDL2_image](http://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz) development library to this directory and unzip it

* SDL2_ttf: 
  
> dwonload [SDL2_ttf](http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-mingw.tar.gz) development library to this directory and unzip it

* LUA: 
  
1. download [LuaDist](https://github.com/LuaDist/Binaries/archive/LuaDist-batteries-0.9.8-Windows-x86.zip) Source Code to this directory.
2. unzip it
3. open `./library/lua-5.4.3/` directory
4. edit the file `Makefile` and change the line `PLAT= guess` to `PLAT= mingw`
5. open the terminal in this direcotry and run `make` command.
6. check the `iblua.a` file in `src` directory, if you can find it , congrats, you have succeed!


