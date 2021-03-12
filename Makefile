CC=g++
CCFLAGS=-std=c++17 -Wall -O3
TARGET=main

all: $(TARGET)

# %.o: %.cpp
# 	$(CC) $(CCFLAGS) -c $<

# %: %.o
# 	$(CC) $^ -o $@

# main: main.cpp fileOperator.o $(CC) $(CCFLAGS) fileOperator.o -o $@ 

main: 
	$(CC) $(CCFLAGS) -c ./lib/*.hpp ./lib/*.cpp
	$(CC) $(CCFLAGS)  main.cpp  *.o -o main
	-mkdir .compiled
	-mv ./lib/*.gch ./.compiled/
	-mv *.o .compiled/

clean:
	-rm -rf .compiled
	-rm main
