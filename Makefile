
CC=gcc -std=c99 -Wall -Wextra -O2 -pedantic
C=$(shell find . -name "*.c")
OUT=teachess.out
LNK=-lSDL2 -lSDL2_image -lSDL2_ttf -ljson-c

build:
	@$(CC) -o $(OUT) $(C) $(LNK) -Wall

dbuild:
	@$(CC) -o $(OUT) $(C) $(LNK) -Wall -g

clean:
	@if [ -f $(OUT) ]; then rm $(OUT); fi

exec:
	@./$(OUT)

