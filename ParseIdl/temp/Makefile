CC = g++
PROGNAME = main
FLAGS = -Wall -ansi -pedantic
SOURCES = InUse.cpp Fork_Item.cpp Philosopher.cpp  Component.cpp main.cpp


all : $(PROGNAME)

.cpp.o : $(CC) $(FLAGS) -c $^

$(PROGNAME) : $(SOURCES:.cpp=.o)
	$(CC) $(SOURCES:.cpp=.o) $(FLAGS) -o $(PROGNAME)

clean :
	@rm -f $(PROGNAME) *.o *~ *.h.gch *\#
	@ls

cc:
	make clean
	@make al

