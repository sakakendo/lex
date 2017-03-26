DEF= -D__DEBUG__
SRC=main.c
INC	=-I.
INC+=-I./inc
ARGS="prog"
CFLAGS +=$(DEF) -Wall

all:$(SRC)
	@gcc $(SRC) $(CFLAGS) $(INC) -o ./a
	@./a $(ARGS)

