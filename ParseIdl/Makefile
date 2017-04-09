CC = g++-4.9
PROGNAME = main
SOURCE = Item.cpp Atom.cpp Container.cpp ContainerInherit.cpp Function.cpp Parameter.cpp ParseurIdl.cpp DidNotFoundFileExcep.cpp FilePair.cpp IdlToCpp.cpp main.cpp
HEADER= Atom.h Container.h Item.h Function.h Parameter.h ParseurIdl.h ContainerInherit.h DidNotFoundFileExcep.h FilePair.h IdlToCpp.h 
FLAGS = -Wall -ansi -pedantic -std=c++11


#ARCHIVE = $(PROGNAME).tar.gz#

all : $(PROGNAME)

DidNotFoundFileExcep.o:DidNotFoundFileExcep.cpp
Item.o: Item.cpp 
ContainerInherit.o: ContainerInherit.cpp
Atom.o: Atom.cpp
Container.o :Container.cpp
Function.o: Function.cpp
Parameter.o: Parameter.cpp
ParseurIdl.o: ParseurIdl.cpp
main.o: main.cpp



.cpp.o: 
	$(CC) $(FLAGS) -c $^

$(PROGNAME) : $(SOURCE:.cpp=.o)
	$(CC) $(SOURCE:.cpp=.o) $(FLAGS) -o $(PROGNAME) 

clean :
	@rm -f $(PROGNAME) *.o *~ *.h.gch *\#
	@ls 

cc:
	@rm -f $(PROGNAME) *.o *~ *.h.gch *\#
	@ls 
	@make
