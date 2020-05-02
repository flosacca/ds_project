# Variables ------------------

HDRS := $(wildcard src/*.h)

# Template libraries
LIBS := $(wildcard src/lib/*.h)

SRCS := $(filter-out src/main.cc,$(wildcard src/*.cc))
OBJS := $(patsubst src/%.cc,obj/%.o,$(SRCS))

FLAGS := -std=c++14 -O3 -static -I src/lib

# Main rules -----------------

all: mkdir bin/main.exe

bin/%.exe: src/%.cc $(HDRS) $(LIBS) $(OBJS)
	g++ $(FLAGS) -o $@ $< $(OBJS)

obj/%.o: src/%.cc $(HDRS) $(LIBS)
	g++ $(FLAGS) -c -o $@ $<

.PRECIOUS: obj/%.o

# Other rules ----------------

.PHONY: all clean mkdir run

clean:
	rm -r obj

mkdir:
	mkdir -p bin obj

run:
	bin/main.exe
