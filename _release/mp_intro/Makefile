CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

linkage: main.o intro.o HSLApixel.o PNG.o lodepng.o
	clang++ main.o PNG.o HSLAPixel.o lodepng.o intro.o  -o intro


main.o: main.cpp intro.h cs225/PNG.h cs225/HSLAPixel.h
	clang++ -c main.cpp

into.o:intro.cpp intro.h
	clang++ -c intro.cpp

PNG.o:cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	clang++ -c cs225/PNG.cpp

HSLApixel.o:cs225/HSLApixel.cpp cs225/HSLApixel.h
	clang++ -c cs225/HSLApixel.cpp

lodepng.o: cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	clang++ -c cs225/lodepng/lodepng.cpp


test: tests.o PNG.o HSLAPixel.o lodepng.o intro.o
	$(LD) tests.o PNG.o HSLAPixel.o lodepng.o intro.o $(LDFLAGS) -o test

tests.o: tests/tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) tests/tests.cpp
