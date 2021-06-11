## SDL2

* download sdl2 (http://www.libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz)
* unzip the compressed file
* copy `SDL2-2.0.14\x86_64-w64-mingw32\` to `./SDL2/` directory 
* copy `SDL2-2.0.14\x86_64-w64-mingw32\bin\SDL2.dll` to the root directory (executable program need this file in runtime)
* install msys2 (https://www.msys2.org/)
* install mingw in msys2 with `pacman -S mingw-w64-x86_64-toolchain base-devel`
* comfirm gcc is the one just we downloaded with `which gcc`
* build program with commands below
  * with console：`gcc test.c -I path\include -L path\lib -l SDL2`
  * without console：`gcc test.c -I path\include -L path\lib -l SDL2 -mwindows`