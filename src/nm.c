/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:41:43 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/24 17:56:43 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

void	print_out(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;

	array = (void *) ptr + symoff;
	stringtable = (void *) ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		ft_putstr(stringtable + array[i].n_un.n_strx);
		ft_putstr("\n");
		i++;
	}
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
			print_out(sym->nsyms, sym->symoff, sym->stroff, ptr);
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
