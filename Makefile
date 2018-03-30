# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchristo <dchristo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/23 13:25:22 by dchristo          #+#    #+#              #
#    Updated: 2018/03/30 14:50:33 by dchristo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: nm otool

nm:
	@make -C ft_nm/

otool:
	@make -C ft_otool/

re: fclean all

clean:
	@make -C ft_nm/ clean
	@make -C ft_otool/ clean

fclean:
	@make -C ft_nm/ fclean
	@make -C ft_otool/ fclean
