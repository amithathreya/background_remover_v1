CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/background.c
OUT = build/background_subtraction		

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) -lm

clean:
	rm -f $(OUT)
