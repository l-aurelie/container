NAME = container
SRC = tests.cpp
OBJ = ${SRC:.cpp=.o}
INCLUDES = vector.hpp vector_iterator.hpp iterator_traits.hpp reverse_iterator.hpp enable_if.hpp vector_iterator.hpp vector_const_iterator.hpp algorithm.hpp map_const_iterator.hpp map_iterator.hpp map.hpp pair.hpp stack.hpp tree.hpp
FLAGS = -Wall -Wextra -Werror   -std=c++98 
#-g3 -fsanitize=address

all: ${NAME} 

%.o: %.cpp ${INCLUDES}
	c++ ${FLAGS} -c $< -o $@

${NAME}: ${OBJ} ${INCLUDES}
	c++ ${FLAGS} ${OBJ} -o ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re