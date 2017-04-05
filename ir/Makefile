
all:main
	clang -c -S -emit-llvm main.c
	llc main.ll

clean:
	rm ./main
