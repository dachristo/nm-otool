# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:35:46 by dchristo          #+#    #+#              #
#    Updated: 2017/05/23 18:46:30 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm-otool

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCDIR = src

CFILES = main.c nm.c otool.c

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
