CXX = clang

all:
	$(CXX) *.c -I . -Wall -o main

clean:
	rm main