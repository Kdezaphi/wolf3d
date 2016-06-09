# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/11 08:47:42 by kdezaphi          #+#    #+#              #
#    Updated: 2016/06/09 14:06:36 by kdezaphi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_DIR = srcs/
SRC = wolf3d.c ft_event.c ft_calc.c ft_trace.c ft_data_file.c ft_pixel.c

OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

INC = -Ilib/incs -Iincs -Iminilibx_macos

LIB_DIR = lib/
MLX_DIR = minilibx_macos/
LIB_LNK = -L$(MLX_DIR) -lmlx -L$(LIB_DIR) -lftprintf -lft -llst \
	-framework AppKit -framework OpenGL
LIB = $(addprefix $(LIB_DIR), libft.a libftprintf.a liblst.a)
MLX = $(MLX_DIR)libmlx.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIB) $(MLX) $(OBJ_DIR) $(OBJ)
	@echo "\033[32mCreation de l'executable $@.\033[0m"
	@$(CC) $(CFLAGS) $(LIB_LNK) $(OBJ) -o $(NAME)

$(LIB):
	@make -C $(LIB_DIR)

$(MLX):
	@make -C $(MLX_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "\033[34mCreation du fichier objet $@.\033[0m"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make -C lib clean
	@make -C $(MLX_DIR) clean
	@echo "\033[35mSuppression des objets.\033[0m"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C lib fclean
	@echo "\033[31mSuppression du fichier $(NAME).\033[0m"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
