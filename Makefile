COMPILER=-Iengine/include/ -O3 -g -fpermissive -w
ENGINELINKER= -ldorian
LINKER=-Lengine/lib/ -Lbuild/ -lmingw32 -lSDL2main -lSDL2 -llua51 -lopengl32

# Takes a lua script, converts it to a string variable file (.clua), and compiles it to a .lua.o
CONVERT_LUA:
	echo WIP

COMPILE_LUA:
	gcc *.clua -c -o 

COMPILE_CPP:
	g++ assets/$(FILE) -c $(COMPILER)

build_engine:
	g++ engine/src/Engine/*.cpp $(COMPILER) $(LINKER) -shared -o build/dorian.dll -DDEBUG_LEVEL1

build_game:
	g++ Engine/src/main.cpp $(ENGINELINKER) $(LINKER) $(COMPILER) -o build/game.exe

test: build_game
	./build/game.exe

clean:
	rm *.o || del *.o