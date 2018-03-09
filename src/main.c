/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:40:52 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/24 17:44:51 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

int	main(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 1)
	{
		if (check_file("a.out", argc) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		while (++i < argc)
			if (check_file(argv[i], argc) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
