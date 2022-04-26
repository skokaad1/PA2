# PA2 Makefile template
CC	=	gcc
CXX	=	g++
CXXFLAGS	=       -std=c++14 -pedantic -Wall
CFLAGS	= 	-Wall -pedantic -g3 
#-fsanitize=address
LIBS	=	
#-lpthread
LFLAGS = 
#-pthread -lrt

# all .o modules to make
#         ls *.cpp | sed 's/.cpp/.o/g' | tr '\n' ' '
MODULES	= 

# all programs to build
#         ls *.cpp | sed 's/.cpp//g' | tr '\n' ' '
ALL	= 

# build all
default:	$(ALL) $(MODULES)

# make dependencies
depend:	
	g++ -MM *.cpp >>Makefile

# clean up
clean:	
	rm -f $(MODULES) $(ALL) core

# link a program from several modules
#prog : $(MODULES) Makefile
#	$(CXX) $(LFLAGS) $(MODULES) -o $@

# compile & link a C++ program
% : %.cpp Makefile
	$(CXX) $(CXXFLAGS) $< $(LFLAGS) $(MODULES) -o $@

# compile a C++ module
%.o : %.cpp Makefile
	$(CXX)  $(CXXFLAGS) -c $< -o $@
#
# here add output of "g++ -MM *.cpp >>Makefile"
