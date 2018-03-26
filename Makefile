GRAALVM=~/graalvm

all:
	cd cext ; $(GRAALVM)/bin/ruby extconf.rb ; make 

clean:
	-rm -f cext/*.bc
	-rm -f cext/*.su
	-rm -f cext/Makefile
