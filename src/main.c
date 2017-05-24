/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:40:52 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/24 16:01:17 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm-otool.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("pas d'argument\n");
		return (EXIT_FAILURE);
	}
	if (start_nm(argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	otool();
	return (EXIT_SUCCESS);
}
