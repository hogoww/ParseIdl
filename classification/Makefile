CC = g++-4.9
PROGNAME = main
SOURCE = Atom.cpp Container.cpp Item.cpp Function.cpp Parameter.cpp ParseurIdl.cpp ContainerInherit.cpp main.cpp
HEADER= Atom.h Container.h Item.h Function.h Parameter.h ParseurIdl.h ContainerInherit.h 
FLAGS = -Wall -ansi -pedantic -std=c++11

#ARCHIVE = $(PROGNAME).tar.gz#

all : $(PROGNAME)

ContainerInherit.o: ContainerInherit.cpp ContainerInherit.h
Atom.o: Atom.cpp Atom.h
Container.o :Container.cpp Container.h 
Item.o: Item.cpp Item.h
Function.o: Function.cpp Function.h
Parameter.o: Parameter.cpp Parameter.h
ParseurIdl.o: ParseurIdl.cpp ParseurIdl.h
main.o: main.cpp



.cpp.o: 
	$(CC) $(FLAGS) -c $^

$(PROGNAME) : $(SOURCE:.cpp=.o)
	$(CC) $(SOURCE:.cpp=.o) $(FLAGS) -o $(PROGNAME) 

clean :
	@rm -f $(PROGNAME) *.o *~ *.h.gch *\#
	@ls 

# launch : 
# 	./launch.sh


