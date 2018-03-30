/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 17:07:21 by kperreau          #+#    #+#             */
/*   Updated: 2015/09/23 17:17:35 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

void		print_head_64(struct section_64 *section, char *name,
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
	if (print != -1 && section->size != 0)
		ft_print_hex(section->addr, 16, "", "\t");
	else if (print == -1 && section->size != 0)
		ft_print_hex(section->addr, 16, "", " ");
}

void		print_hex_64(char *ptr, struct section_64 *section,
		char *name, int print)
{
	int						k;
	char					c;
	struct mach_header		*h;

	h = (struct mach_header*)ptr;
	k = 0;
	print_head_64(section, name, print);
	while (k < (int)section->size)
	{
		c = *(ptr + (int)(section->offset) + k++);
		ft_print_section(c);
		if (print != -1 && k % 16 == 0 && k != (int)section->size)
			ft_print_hex(section->addr + k, 16, " \n", "\t");
		else if (print == -1 && k % 16 == 0 && k != (int)section->size)
			ft_print_hex(section->addr + k, 16, " \n", " ");
		else
			ft_putchar(' ');
	}
	if (section->size != 0)
		ft_putchar('\n');
}

void		print_head(struct section *section, char *name, int print)
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
	if (print != -1 && section->size != 0)
		ft_print_hex(section->addr, 8, "", "\t");
	else if (print == -1 && section->size != 0)
		ft_print_hex(section->addr, 8, "", " ");
}

void		print_hex(char *ptr, struct section *section,
		char *name, int print)
{
	int		k;
	char	c;

	k = 0;
	print_head(section, name, print);
	while (k < (int)section->size)
	{
		c = *(ptr + (int)(section->offset) + k++);
		ft_print_section(c);
		if (print != -1 && k % 16 == 0 && k != (int)section->size)
			ft_print_hex(section->addr + k, 8, " \n", "\t");
		else if (print == -1 && k % 16 == 0 && k != (int)section->size)
			ft_print_hex(section->addr + k, 8, " \n", " ");
		else
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

void		fat_header(T_FAT_HEADER *header, T_FAT_ARCH *arch)
{
	int i;

	i = -1;
	ft_putstr("Fat headers\nfat_magic 0x");
	ft_puthex(ft_rev_int(header->magic));
	ft_putstr("\nnfat_arch ");
	ft_putnbr(ft_rev_int(header->nfat_arch));
	ft_putstr("\n");
	while (++i < (int)ft_rev_int(header->nfat_arch))
	{
		print_arch("architecture ", "\n    ", i);
		print_arch("cputype ", "\n    ", ft_rev_int(arch->cputype));
		print_arch("cpusubtype ", "\n    ", ft_rev_int(arch->cpusubtype) &
				~CPU_SUBTYPE_MASK);
		print_arch_hex("capabilities 0x", "\n    ", arch->cpusubtype &
				~CPU_SUBTYPE_MASK);
		print_arch("offset ", "\n    ", ft_rev_int(arch->offset));
		print_arch("size ", "\n    ", ft_rev_int(arch->size));
		print_arch_double("align 2^", ft_rev_int(arch->align),
				1 << ft_rev_int(arch->align));
		arch = (void*)arch + sizeof(*arch);
	}
}
