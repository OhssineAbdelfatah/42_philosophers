# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/27 10:35:06 by aohssine          #+#    #+#              #
#    Updated: 2024/11/16 11:45:43 by blacksniper      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror  -Wall -g -fsanitize=thread
RM = rm -rf
SRC = dinner.c getters_setters.c main.c monitoring.c parsing.c syncro.c utils.c  write.c 

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