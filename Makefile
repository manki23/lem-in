# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manki <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/01 17:31:36 by manki             #+#    #+#              #
#    Updated: 2019/09/04 10:36:27 by manki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##  VARIABLES   ##
##################

NAME = lem-in

SRC_PATH = ./src/
INC_PATH = ./inc/
OBJ_PATH = ./obj/
LIB_PATH = ./libft/

SRC_NAME = main.c

INC_NAME = lem_in.h
LIB_NAME = libft.a

OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix $(INC_PATH), $(INC_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB = $(addprefix $(LIB_PATH), $(LIB_NAME))

FLAGS = -Wall -Wextra -Werror
CC = gcc


##################
##    COLORS    ##
##################

_GREY=$ \033[30m
_RED=$ \033[31m
_GREEN=$ \033[32m
_YELLOW=$ \033[33m
_BLUE=$ \033[34m
_PURPLE=$ \033[35m
_CYAN=$ \033[36m
_WHITE=$ \033[37m
_END=$ \033[0m

##################
##   TARGETS    ##
##################

.PHONY: all clean fclean re

all: $(LIB) $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(LIB) $(INC) $(OBJ)
	$(CC) $(FLAGS) $(SRC) $(LIB) -o $(NAME)
	echo "\n✅  $(_GREEN)$(NAME) created 😎 $(_END)"

$(LIB): FORCE
	make -C libft all

FORCE:

clean:
	make -C libft clean
	/bin/rm -rf $(OBJ_PATH)
	echo "❌  $(_RED)OBJECT FILES DELETED 😱 $(_END)"

fclean: clean
	make -C libft fclean
	/bin/rm -f $(NAME)
	echo "❌  $(_RED)$(NAME) DELETED 😱 $(_END)"

re: fclean all

norme:
	norminette $(INC_PATH) $(SRC_PATH)

.SILENT:
