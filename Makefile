COMPILER=-Iinclude/ -O0 -g -fpermissive -w -Wall -std=c++2a
ENGINELINKER= -ldorian
LINKER=-Llib/$(OS)/ -Lbuild/$(OS)/ -lmingw32 -lSDL2main -lSDL2 -llua51 -lopengl32 -lglew32

STORE=DEVELOPMENT

COMPILE_CPP:
	g++ -o ./tmp/$(FILE).o $(FILE) -c $(COMPILER)

build_engine:
	g++ src/Engine/*.cpp src/format.cc $(COMPILER) $(LINKER) -shared -o build/$(OS)/dorian.dll -D DEBUG_LEVEL1

build_game:
	g++ src/main.cpp $(ENGINELINKER) $(LINKER) $(COMPILER) -o build/$(OS)/game.exe -D BUILD_$(STORE)

build_test:
	g++ tests/$(TEST).cpp $(ENGINELINKER) $(LINKER) $(COMPILER) -o build/$(OS)/$(TEST).exe -DDORIAN_TESTFILE

run_test: build_test
	cd build/$(OS) && ./$(TEST).exe

clean:
	rm ./tmp/*.o || del *.o