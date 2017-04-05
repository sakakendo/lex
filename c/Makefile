SRC=main.c
INC	=-I.
INC+=-I../workspace/compiler/
ARGS="prog"
DEF= -D__DEBUG__
CFLAGS +=$(DEF) -Wall

all:$(SRC)
	gcc $(SRC) $(CFLAGS) $(INC) -o ./a
	@./a $(ARGS)

