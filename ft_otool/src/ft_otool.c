/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:05:44 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/23 16:05:45 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

static t_file_ptr	*save_ptr(char *ptr, int size, char *ptr_end,
							   t_options *options)
{
	t_file_ptr *ptr_file;

	ptr_file = (t_file_ptr *)malloc(sizeof(struct s_file_ptr) * 1);
	ptr_file->ptr_free = ptr;
	ptr_file->ptr = ptr;
	ptr_file->ptr_end = ptr_end;
	ptr_file->size = size;
	ptr_file->options = options;
	return (ptr_file);
}

static int			ft_is_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

static int			check_magic(t_file_ptr *ptr_file, char *file)
{
	unsigned int magic_number;

	magic_number = *(unsigned int *)ptr_file->ptr;
	if (magic_number == MH_MAGIC_64)
	{
		return (ft_handle64((struct mach_header_64 *)ptr_file->ptr,
							ptr_file, file, 0));
	}
	else if (magic_number == MH_MAGIC)
	{
		return (ft_handle32((struct mach_header *)ptr_file->ptr,
							ptr_file, file, 0));
	}
	else if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
	{
		return (ft_fat_handle((struct fat_header *)ptr_file->ptr,
							  ptr_file, file));
	}
	else if (!ft_strncmp(ptr_file->ptr, ARMAG, SARMAG))
		return (ft_lib(ptr_file, file, ptr_file->size));
	else
		ft_error_object(file);
	return (0);
}

int					check_file(char *file, t_options *options)
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
	return (check_magic(save_ptr(ptr, buf.st_size, ptr + buf.st_size, options),
						file));
}
