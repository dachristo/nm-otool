# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <dchristo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/15 11:35:46 by dchristo          #+#    #+#              #
#    Updated: 2018/03/23 13:26:58 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_otool

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCDIR = src

CFILES = main.c ft_fat.c ft_lib.c ft_handle32.c ft_otool.c ft_error.c ft_tools.c \
        check_error.c libft.c libft2.c libft3.c ft_display_32.c ft_display_64.c \
        print.c print_data.c ft_handle64.c

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
