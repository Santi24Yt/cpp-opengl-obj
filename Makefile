CC = g++

CFLAGS = -xc++ -std=c++11
DFLAGS = -Wall -Werror

INCLUDES = -I./libs/
LIBS = -lglfw -lGL -lGLEW

SOURCES = $(wildcard **/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

OUT = openglobj

all: lspflags $(OUT)

$(OUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUT)

lspflags:
	echo $(INCLUDES) $(LIBS) $(DFLAGS) $(CFLAGS) | sed "s/ /\n/g" > compile_flags.txt
