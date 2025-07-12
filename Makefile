CC = cc

CFLAGS= -Wall -Wextra -Werror

SRC = routine.c utils2.c philo.c utils.c mon.c 

OBJ = $(SRC:%.c=%.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean  all

.SECONDARY: $(OBJ)
.PHONY: re fclaen clean all
