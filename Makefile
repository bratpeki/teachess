
CC=gcc
C=$(shell find . -name "*.c")
OUT=teachess.out
LNK=-lSDL2 -lSDL2_image -ljson-c

all:
	@make build exec

build:
	@$(CC) -o $(OUT) $(C) $(LNK)

clean:
	@if [ -f $(OUT) ]; then rm $(OUT); fi

exec:
	@./$(OUT)
