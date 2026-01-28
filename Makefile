CXX = g++
FLAGS = -Wall -Wextra -Werror
LIBS = -lm
SRC = matrix.cpp vector.cpp 

%.o : %.cpp
	$(CXX) $(FLAGS) $(LIBS) -c $^

all : matrix.o vector.o 

clean :
	@rm -f *.o
