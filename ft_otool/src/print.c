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

static void	ft_put_zero(size_t size, int arch)
{
	int nb;

	nb = ft_puthex_nb(size, 1);
	while (arch > nb++)
		ft_putchar('0');
}

static void	ft_print_hex(size_t size, int arch, char *start, char *end)
{
	ft_putstr(start);
	ft_put_zero(size, arch);
	ft_puthex(size);
	ft_putstr(end);
}

static void	ft_print_section(unsigned int size)
{
	ft_put_zero(size & 0xFF, 2);
	ft_puthex(size & 0xFF);
}

void				print_head_64(struct section_64 *section, char *name,
		int print)
{
	if (print == 0)
		printf("%s:\n", name);
	printf("(%s,%s) section\n", section->segname, section->sectname);
	if (print != -1 && section->size != 0)
		ft_print_hex(section->addr, 16, "", " ");
	else if (print == -1 && section->size != 0)
		ft_print_hex(section->addr, 16, "", "\t");
}

void				print_hex_64(char *ptr, struct section_64 *section,
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
			ft_print_hex(section->addr + k, 16, " \n", " ");
		else if (print == -1 && k % 16 == 0 && k != (int)section->size)
			ft_print_hex(section->addr + k, 16, " \n", "\t");
		else
			ft_putchar(' ');
	}
	if (section->size != 0)
		ft_putchar('\n');
}

void				print_head(struct section *section, char *name, int print)
{
	if (print == 0)
		printf("%s:\n", name);
	printf("(%s,%s) section\n", section->segname, section->sectname);
	if (print != -1 && section->size != 0)
		printf("%.8x ", section->addr);
	else if (print == -1 && section->size != 0)
		printf("%.8x\t", section->addr);
}

void				print_hex(char *ptr, struct section *section,
		char *name, int print)
{
	int		k;
	char	c;

	k = 0;
	print_head(section, name, print);
	while (k < (int)section->size)
	{
		c = *(ptr + (int)(section->offset) + k++);
		printf("%.2hhx", c);
		if (print != -1 && k % 16 == 0 && k != (int)section->size)
			printf(" \n%.8x ", section->addr + k);
		else if (print == -1 && k % 16 == 0 && k != (int)section->size)
			printf(" \n%.8x\t", section->addr + k);
		else
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

void				fat_header(T_FAT_HEADER *header, T_FAT_ARCH *arch)
{
	int i;

	i = -1;
	printf("Fat headers\nfat_magic 0x%x\nnfat_arch %d\n",
			ft_rev_int(header->magic), ft_rev_int(header->nfat_arch));
	while (++i < (int)ft_rev_int(header->nfat_arch))
	{
		printf("architecture %d\n    ", i);
		printf("cputype %d\n    ", ft_rev_int(arch->cputype));
		printf("cpusubtype %d\n    ", ft_rev_int(arch->cpusubtype) &
				~CPU_SUBTYPE_MASK);
		printf("capabilities 0x%x\n    ", arch->cpusubtype &
				~CPU_SUBTYPE_MASK);
		printf("offset %d\n    ", ft_rev_int(arch->offset));
		printf("size %d\n    ", ft_rev_int(arch->size));
		printf("align 2^%d (%d)\n", ft_rev_int(arch->align),
				1 << ft_rev_int(arch->align));
		arch = (void*)arch + sizeof(*arch);
	}
}
