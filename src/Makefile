CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LIBS = -lportaudio -lwinmm -lole32 -lsetupapi
TARGET = app
SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -L./libs $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I./ -c $< -o $@

clean:
	del *.o *.exe



