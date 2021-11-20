
CC=gcc
C=$(shell find . -name "*.c")
OUT=teachess.out
LNK=-lSDL2 -lSDL2_image -ljson-c

build:
	@$(CC) -o $(OUT) $(C) $(LNK)

clean:
	@if [ -f $(OUT) ]; then rm $(OUT); fi

exec:
	@./$(OUT)

