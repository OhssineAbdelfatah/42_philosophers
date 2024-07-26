CC = cc
CFLAGS = -Wextra -Werror  -Wall #-fsanitize=thread -pthread #-fsanitize=address -g
RM = rm -rf
SRC = philo.c input.c routine.c utils.c

OBJ = $(SRC:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJ) philo.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	$(RM) $(OBJ) 

fclean : clean
	$(RM) $(NAME)

re : fclean all