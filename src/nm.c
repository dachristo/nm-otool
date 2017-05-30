/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:41:43 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/30 19:22:04 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

void	ft_putsymtype(char *str)
{
	if (ft_strcmp("_header", str) == 0)
		ft_putstr("t");
	else if (ft_strcmp("header", str) == 0)
		ft_putstr("T");
	else if (ft_strcmp("", str) == 0)
		ft_putstr("U");
	else
		ft_putstr(str);
}


void	print_out(int *tried, struct symtab_command *sym, char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;

	array = (void *) ptr + sym->symoff;
	stringtable = (void *) ptr + sym->stroff;
	i = 0;
	while (tried[i] != -1)
	{
		if (array[tried[i]].n_value != 0)
		{
			ft_putstr("0000000");
			ft_puthex(array[tried[i]].n_value); // value
		}
		else
			ft_putstr("                ");
		ft_putstr(" ");
		ft_putsymtype(stringtable + array[tried[i]].n_type); // type
		ft_putstr(" ");
		ft_putstr(stringtable + array[tried[i]].n_un.n_strx); // function_name
		ft_putstr("\n");
		i++;
	}
}

int		*tri_before(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;
	int					*tried;
	int					tmp;
	int					j;
	array = (void *) ptr + symoff;
	stringtable = (void *) ptr + stroff;
	i = 0;
	tried = malloc(sizeof(int) * nsyms + 1);
	while (i < nsyms)
	{
		tried[i] = i;
		i++;
	}
	tried[i] = -1;
	i = 0;
	while (tried[i] != -1)
	{
		j = 0;
		while (j < nsyms)
		{
			if (ft_strcmp(stringtable + array[tried[i]].n_un.n_strx, 
				stringtable + array[tried[j]].n_un.n_strx) < 0)
			{
				tmp = tried[i];
				tried[i] = tried[j];
				tried[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tried);
}

void	handle_64(char *ptr)
{
	int						ncmds;
	int 					i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *) ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_out(tri_before(sym->nsyms, sym->symoff, sym->stroff, ptr), sym, ptr);
			break ;
		}
		i++;
		lc = (void *) lc + lc->cmdsize;
	}
}

void	nm(char *ptr)
{
	unsigned int		magic_number;

	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
}

int		start_nm(char *file)
{
	int			fd;
	struct stat buf;
	char		*ptr;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
