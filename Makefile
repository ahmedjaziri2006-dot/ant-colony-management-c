CC = gcc
CFLAGS = -Wall -g
TARGET = programme

SRC = main.c fonctions.c
OBJ = $(SRC:.c=.o)
HEADER = programme.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
