# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 10:18:02 by fgreiff           #+#    #+#              #
#    Updated: 2026/03/24 12:53:47 by fgreiff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g3 -O0

SRC_DIR = src
OBJ_DIR = obj

SRCS =  $(SRC_DIR)/philo.c \
        $(SRC_DIR)/parsing.c \
        $(SRC_DIR)/parsing_utils.c \
        $(SRC_DIR)/utils.c \
        $(SRC_DIR)/routine.c \
		$(SRC_DIR)/routine2.c \
        $(SRC_DIR)/observer_routine.c \
        $(SRC_DIR)/struct_init.c 

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@echo "Object files deleted"

fclean: clean
	rm -f $(NAME)
	@echo "Executable deleted"

re: fclean all

.PHONY: all clean fclean re