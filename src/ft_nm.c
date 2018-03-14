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

static t_file_ptr	*save_ptr(char *ptr, int size, char *ptr_end)
{
	t_file_ptr *ptr_file;

	ptr_file = (t_file_ptr *)malloc(sizeof(struct s_file_ptr) * 1);
	ptr_file->ptr_free = ptr;
	ptr_file->ptr = ptr;
	ptr_file->ptr_end = ptr_end;
	ptr_file->size = size;

	return (ptr_file);
}

static int	check_magic(char *ptr, struct stat buf, char *file, int argc)
{
	unsigned int magic_number;

	magic_number = *(unsigned int *) ptr;
	if ((magic_number == MH_MAGIC_64 || magic_number == FAT_CIGAM ||
		 magic_number == FAT_MAGIC || magic_number == MH_MAGIC ||
		 !ft_strncmp(ptr, file, buf.st_size)) && argc > 2)
	{
		ft_putchar('\n');
		ft_putstr(file);
		ft_putstr(":\n");
	}
	if (magic_number == MH_MAGIC_64)
		ft_handle64((struct mach_header_64 *) ptr, save_ptr(ptr, buf.st_size, ptr + buf.st_size), -1, -1);
	if (magic_number == MH_MAGIC)
		ft_handle32((struct mach_header *) ptr, save_ptr(ptr, buf.st_size, ptr + buf.st_size), -1, -1);
	if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
		ft_fat_handle((struct fat_header *)ptr, save_ptr(ptr, buf.st_size, ptr + buf.st_size), file);
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		ft_lib(save_ptr(ptr, buf.st_size, ptr + buf.st_size), file, buf.st_size);
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
		return (0);
	}
	if (fstat(fd, &buf) < 0)
		return (0);
	if (!ft_is_file(file))
	{
		errno = EISDIR;
		perror(file);
		return (0);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
	{
		perror("mmap");
		return (0);
	}
	return (check_magic(ptr, buf, file, argc));
}
