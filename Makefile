COMPILER=-Iengine/include/ -std=c++20
ENGINELINKER=-Lbuild/ -ldorian
LINKER=-Lengine/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

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
	./build/game.exe

clean:
	rm *.o || del *.o