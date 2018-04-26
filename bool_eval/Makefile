CC=clang
LINK=llvm-link
OPT=opt

CFLAGS=-O0 -g
OPT_FLAGS=-mem2reg

# comment this line when compiling with clang < 5.0
CLANG_ARGS=-Xclang -disable-O0-optnone

all:
	$(CC) $(CFLAGS) $(CLANG_ARGS) -c -emit-llvm -o parse.bc parse.c
	$(CC) $(CFLAGS) $(CLANG_ARGS) -c -emit-llvm -o eval.bc eval.c
	$(LINK) parse.bc eval.bc -o c_boole.bc
	$(OPT) $(OPT_FLAGS) -o c_boole.bc c_boole.bc
	-rm -f parse.bc eval.bc

clean:
	-rm -f *.bc
