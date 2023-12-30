NAME = philosophers

SRC = philo.c\
		init.c\
		run_stat.c\
		cycle_of_life.c\
		toolbox_1.c\
		nightclub_security.c\
	
CFLAGS = -Wall -Wextra -Werror -g

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
				@clang $(OBJ) -pthread -o $(NAME)

clean:
		@rm -f $(OBJ)

fclean: clean
			@rm -f $(NAME)
	
re : fclean all

.PHONY : all clean fclean re
