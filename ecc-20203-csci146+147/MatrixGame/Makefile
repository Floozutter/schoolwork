COMPILER=g++
OPTIONS=-g -std=c++17 -Wall -Wextra
COMPILE=$(COMPILER) $(OPTIONS)

main: src/main.cpp build/Game.o build/Arena.o build/Player.o build/Robot.o build/utilities.o
	$(COMPILE) $< build/*.o -o build/MatrixGame

build/Game.o: src/Game.cpp src/Game.h build/.make src/globals.h src/Arena.h
	$(COMPILE) -c $< -o $@

build/Arena.o: src/Arena.cpp src/Arena.h build/.make src/globals.h src/Player.h src/Robot.h
	$(COMPILE) -c $< -o $@

build/Player.o: src/Player.cpp src/Player.h build/.make src/Arena.h
	$(COMPILE) -c $< -o $@

build/Robot.o: src/Robot.cpp src/Robot.h build/.make src/Arena.h
	$(COMPILE) -c $< -o $@

build/utilities.o: src/utilities.cpp src/globals.h build/.make
	$(COMPILE) -c $< -o $@

build/.make:
	mkdir -p build
	touch build/.make

clean:
	rm -rf build
