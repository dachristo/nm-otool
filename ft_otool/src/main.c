/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 17:06:48 by kperreau          #+#    #+#             */
/*   Updated: 2015/09/22 17:06:50 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

static void	check_options(t_options *options, char **argv, int i, int j)
{
	if (j != 0 && (argv[i][j] == 'd' || argv[i][j] == 'f'))
	{
		if (argv[i][j] == 'd')
			options->flag_d = TRUE;
		else if (argv[i][j] == 'f')
			options->flag_f = TRUE;
	}
	else if (j != 0)
	{
		ft_putstr("Unknow char`");
		ft_putchar(argv[i][j]);
		ft_putstr("' in flag -");
		ft_putchar(argv[i][j]);
		ft_putstr("\n");
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
	options->flag_d = FALSE;
	options->flag_f = FALSE;
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

int		main(int argc, char **argv)
{
	int				i;
	int			result;
	t_options	options;

	i = ft_options(&options, argv, argc);
	while (++i < argc)
	{
		result = check_file(argv[i], &options);
		if (result == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
