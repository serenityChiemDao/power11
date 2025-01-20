
CC = g++
LD = g++
CFLAGS = -std=c++0x -W -Wall --pedantic -DNDEBUG
LDFLAGS =

all: power

power: $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o power s132871_OOPP_Project_2.tar.gz

archive:
	tar czvf s132871_OOPP_Project_2.tar.gz *.?pp makefile

