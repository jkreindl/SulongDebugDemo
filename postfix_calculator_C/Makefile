OPTS=-c -emit-llvm -O1

ifdef NO_DEBUG
	DBG=
else
	DBG=-g
endif

all:
	clang $(OPTS) $(DBG) -o tmp_calc.bc calc.c
	clang $(OPTS) $(DBG) -o tmp_main.bc main.c
	llvm-link -o calc.bc tmp_main.bc tmp_calc.bc
	llvm-dis -o calc.ll calc.bc
	rm -f tmp_main.bc
	rm -f tmp_calc.bc

clean:
	-rm -f *.bc
	-rm -f *.ll