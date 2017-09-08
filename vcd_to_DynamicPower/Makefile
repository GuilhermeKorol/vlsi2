CC = g++
CFLAGS = -g -Wall -I./hdr/
LDFLAGS = -lm

src = $(wildcard *.cpp) \
		  $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

all: clean psw

psw: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) psw
