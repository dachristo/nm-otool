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

static void	check_options(t_options *options, char **argv, int i, int j)
{
	if (j != 0 && (argv[i][j] == 'p' || argv[i][j] == 'r'))
	{
		if (argv[i][j] == 'p')
			options->flag_p = TRUE;
		else if (argv[i][j] == 'r')
			options->flag_r = TRUE;
	}
	else if (j != 0)
	{
		ft_putstr("Unknow command line argument '-");
		ft_putchar(argv[i][j]);
		ft_putstr("'.\n");
		exit(1);
	}
}

static int	ft_options(t_options *options, char **argv, int argc)
{
	int i;
	int j;
	int nb;

	i = 0;
	nb = 0;
	options->flag_p = FALSE;
	options->flag_r = FALSE;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][0] == '-')
			{
				if (j == 0)
					nb += 1;
				check_options(options, argv, i, j);
			}
		}
	}
	options->n = nb;
	return (nb);
}

int			main(int argc, char **argv)
{
	int			i;
	int			result;
	t_options	options;

	i = 0;
	if (argc == 1)
	{
		if (check_file("a.out", argc, &options) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		i = ft_options(&options, argv, argc);
		if (i + 1 == argc)
			if (check_file("a.out", argc, &options) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		while (++i < argc)
			result = check_file(argv[i], argc, &options);
		if (result == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
