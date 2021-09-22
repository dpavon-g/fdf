# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 18:01:15 by dpavon-g          #+#    #+#              #
#    Updated: 2021/09/22 10:05:46 by dpavon-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fdf

SRCS = 	fdf.c

OBJECTS = $(SRCS:.c=.o)
LIB_PATH = libft/
LIB_NAME = $(LIB_PATH)libft.a
INCLUDES = -I. -I$(LIB_PATH)
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $^ -L ./libft/ -l ft -o $@

clean:
	@make -C $(LIB_PATH) clean
	@rm -f $(OBJECTS)

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
