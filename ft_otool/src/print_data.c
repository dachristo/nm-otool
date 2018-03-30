/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 17:06:57 by kperreau          #+#    #+#             */
/*   Updated: 2015/09/22 17:06:58 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

static void			print_head_data_64(struct section_64 *section, char *name,
		int print)
{
	if (print == 0)
	{
		ft_putstr(name);
		ft_putstr(":\n");
	}
	ft_putstr("Contents of (");
	ft_putstr(section->segname);
	ft_putstr(",");
	ft_putstr(section->sectname);
	ft_putstr(") section\n");
	if (section->size != 0)
		ft_print_hex(section->addr, 16, " \n", "\t");
}

static void			print_head_data(struct section *section, char *name,
		int print)
{
	if (print == 0)
	{
		ft_putstr(name);
		ft_putstr(":\n");
	}
	ft_putstr("Contents of (");
	ft_putstr(section->segname);
	ft_putstr(",");
	ft_putstr(section->sectname);
	ft_putstr(") section\n");
	if (section->size != 0)
		ft_print_hex(section->addr, 8, "", "\t");
}

void				print_hex_data_64(char *ptr, struct section_64 *section,
		char *name, int print)
{
	int						k;
	char					c;
	struct mach_header		*h;

	h = (struct mach_header*)ptr;
	k = 0;
	print_head_data_64(section, name, print);
	while (k < (int)section->size)
	{
		c = *(ptr + (int)(section->offset) + k++);
		ft_print_section(c);
		if (k % 16 == 0 && k != (int)section->size)
			ft_print_hex(section->addr + k, 16, " \n", "\t");
		else
			ft_putchar(' ');
	}
	if (section->size != 0)
		ft_putchar('\n');
}

void				print_hex_data(char *ptr, struct section *section,
			char *name, int print)
{
	int		k;
	char	c;

	ft_putstr("IN 32\n");
	k = 0;
	print_head_data(section, name, print);
	while (k < (int)section->size)
	{
		c = *(ptr + (int)(section->offset) + k++);
		ft_print_section(c);
		if (k % 16 == 0 && k != (int)section->size)
			ft_print_hex(section->addr + k, 8, " \n", "\t");
		else
			ft_putchar(' ');
	}
	ft_putchar('\n');
}
