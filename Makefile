
CC=gcc -std=c99
C=$(shell find . -name "*.c")
OUT=teachess.out
LNK=-lSDL2 -lSDL2_image -lSDL2_ttf -ljson-c

build:
	@$(CC) -o $(OUT) $(C) $(LNK)

clean:
	@if [ -f $(OUT) ]; then rm $(OUT); fi

exec:
	@./$(OUT)

