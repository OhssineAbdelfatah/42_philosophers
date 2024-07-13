CC = cc
CFLAGS = -Wextra -Werror  -Wall 
RM = rm -rf
SRC = philo.c utils.c input.c

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