# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:35:46 by dchristo          #+#    #+#              #
#    Updated: 2017/05/31 17:48:01 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

CC = gcc

#CFLAGS = -Wall -Wextra -Werror

SRCDIR = src

CFILES = main.c ft_nm.c libft.c ft_data.c ft_sort.c ft_handle.c ft_display_64.c \
            ft_display_32.c check_error.c ft_fat.c ft_lib.c libft2.c ft_tools.c \
            ft_sort32.c ft_sort64.c libft3.c

SRC = $(patsubst %, $(SRCDIR)/%, $(CFILES))

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0m";
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;5;1;36m";
	@echo "+-------------------------------------------------+";
	@echo "|  _   _                  ____  _              _  |";
	@echo "| | \ | |                / __ \| |            | | |";
	@echo "| |  \| |_ __ ___ ______| |  | | |_ ___   ___ | | |";
	@echo "| | . \` | '_ \` _ \\______| |  | | __/ _ \\ / _ \\| | |";
	@echo "| | |\  | | | | | |     | |__| | || (_) | (_) | | |";
	@echo "| |_| \_|_| |_| |_|      \____/ \__\___/ \___/|_| |";
	@echo "|                                                 |";
	@echo "+-------------------------------------by dchristo-+"; 
	@echo "\033[0m";

clean:
	@rm -rf $(OBJS)
	@echo "Clean done"

fclean: clean
	@rm -rf $(NAME) $(LS)
	@echo "Fclean done"

re: fclean all

%.o: %.c
			$(CC) -c $< $(CFLAGS) -o $@

.PHONY: clean fclean re all
