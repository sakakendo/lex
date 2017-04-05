DEF=-D__DEBUG__
SRC=main.c
INC	=-I.
INC+=-I../../workspace/compiler/inc/
INC+=-I../../workspace/

ARGS="+++++++[>+++++++<-]>+."
CFLAGS +=$(DEF) -Wall

all:$(SRC)
	gcc $(SRC) $(CFLAGS) $(INC) -o ./a
	@./a $(ARGS)

