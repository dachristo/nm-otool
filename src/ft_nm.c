/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:41:43 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/09 18:05:41 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

static int	check_magic(char *ptr, struct stat buf, char *file, int argc)
{
	unsigned int magic_number;

	magic_number = *(unsigned int *)ptr;
	if ((magic_number == MH_MAGIC_64 || magic_number == FAT_CIGAM ||
			magic_number == FAT_MAGIC || magic_number == MH_MAGIC ||
			!ft_strncmp(ptr, file, buf.st_size)) && argc > 2)
	{
		ft_putchar('\n');
		ft_putstr(file);
		ft_putstr(":\n");
	}
	if (magic_number == MH_MAGIC_64)
		ft_handle64(ptr, (struct mach_header_64 *)ptr);
	if (magic_number == MH_MAGIC)
		ft_handle32(ptr, (struct mach_header *)ptr);
//	if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
//		ft_fat_handle(ptr, (struct fat_header *)ptr, file);
//	if (!ft_strncmp(ptr, ARMAG, SARMAG))
//		ft_lib(ptr, file, buf.st_size);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	return (0);
}

static int	ft_is_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int			check_file(char *file, int argc)
{
	int			fd;
	struct stat	buf;
	char		*ptr;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		perror(file);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
		return (EXIT_FAILURE);
	if (!ft_is_file(file))
	{
		errno = EISDIR;
		perror(file);
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	return (check_magic(ptr, buf, file, argc));
}
