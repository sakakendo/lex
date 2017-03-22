DEF= -D__DEBUG__
SRC=main.c
INC=.
ARGS="prog"
CFLAGS +=$(DEF) -Wall

all:$(SRC)
	@gcc $(SRC) $(CFLAGS) -I$(INC) -o ./a
	@./a $(ARGS)

