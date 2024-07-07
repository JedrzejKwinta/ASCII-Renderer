.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))
SYSNAME = $(shell uname -s)

NAME1 = art

EXEC1  = $(NAME1).x

CFG = cfg.txt

OBJS1  = $(NAME1).o


LDLIBS = -lm

CO = g++
LD = $(CO)

CFLAGS = -std=c++20 
LFLAGS = -std=c++20

AR = ar

ARFLAGS = rsv

%.x: %.cpp
	$(CO) $(CFLAGS) $^ -o $@

.PHONY: all
all: $(EXEC1)

###############################################################################
.PHONY: run
###############################################################################
run: $(EXEC1)
	./$(EXEC1) $(CFG)
###############################################################################
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out output.txt

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
