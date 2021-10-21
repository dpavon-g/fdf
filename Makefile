# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 18:01:15 by dpavon-g          #+#    #+#              #
#    Updated: 2021/10/21 17:58:19 by dpavon-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
LINK = -lmlx -framework OpenGL -framework AppKit
NAME = fdf

SRCS = 	src/fdf.c\
		src/charge_map.c\
		src/get_color.c\
		src/know_dates.c\
		src/start_draw.c\
		src/errors.c\
		src/bresenham.c\
		src/mlx_options.c

OBJECTS = $(SRCS:.c=.o) 
LIB_PATH = libft/
LIB_NAME = $(LIB_PATH)libft.a
INCLUDES = -I. -I$(LIB_PATH)
FSANITIZE = -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -s -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(LINK) $^ -L ./libft/ -l ft -o $@
	
clean:
	@make -C $(LIB_PATH) clean
	@rm -f $(OBJECTS)

normi:
	norminette $(SRCS)

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all debug clean fclean re
