COMPILER=-Iengine/include/ -O3
ENGINELINKER= -ldorian
LINKER=-Lengine/lib/ -Lbuild/ -lraylib -lopengl32 -lgdi32 -lwinmm -llua51

# Takes a lua script, converts it to a string variable file (.clua), and compiles it to a .lua.o
CONVERT_LUA:
	echo WIP

COMPILE_LUA:
	gcc *.clua -c -o 

COMPILE_CPP:
	g++ assets/$(FILE) -c $(COMPILER)

build_engine:
	g++ engine/src/Engine/*.cpp $(COMPILER) $(LINKER) -shared -o build/dorian.dll

build_game:
	g++ Engine/src/main.cpp $(ENGINELINKER) $(LINKER) $(COMPILER) -o build/game.exe

test: build_game
	cd build && ./build/game.exe

clean:
	rm *.o || del *.o