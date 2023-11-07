COMPILER=-Iengine/include/ -O3 -g -fpermissive -w
ENGINELINKER= -ldorian
LINKER=-Lengine/lib/$(OS)/ -Lbuild/$(OS)/ -lmingw32 -lSDL2main -lSDL2 -llua51 -lopengl32 -lglew32

# Takes a lua script, converts it to a string variable file (.clua), and compiles it to a .lua.o
CONVERT_LUA:
	echo WIP

COMPILE_LUA:
	gcc *.clua -c -o 

COMPILE_CPP:
	g++ -o ./engine/tmp/$(FILE).o $(FILE) -c $(COMPILER)

build_engine:
	g++ engine/src/Engine/*.cpp $(COMPILER) $(LINKER) -shared -o build/$(OS)/dorian.dll -D DEBUG_LEVEL1

build_game:
	g++ Engine/src/main.cpp $(ENGINELINKER) $(LINKER) $(COMPILER) -o build/$(OS)/game.exe 

test: build_game
	cd build/$(OS) && .\game.exe

clean:
	rm ./engine/tmp/*.o || del *.o