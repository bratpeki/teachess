
CC=gcc
C=$(shell find . -name "*.c")
OUT=teachess.out
LNK=-lSDL2

all:
	@make build exec

build:
	@$(CC) -o teachess $(C) $(LNK)

clean:
	@if [ -f $(OUT) ]; then rm $(OUT); fi

exec:
	@./$(OUT)

