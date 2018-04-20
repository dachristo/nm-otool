/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:29:31 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/14 14:29:33 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

int	check_ptr(void *ptr, char *error, t_file_ptr *ptr_file)
{
	if (ptr > ptr_file->ptr_end)
	{
		ft_putstr(error);
		if (munmap(ptr_file->ptr_free, ptr_file->size) < 0)
			return (1);
		free(ptr_file);
		return (1);
	}
	return (0);
}

int	check_lc(int cmdsize, int i, int ncmds, t_file_ptr *ptr_file)
{
	if (cmdsize == 0 && i + 1 != ncmds)
	{
		ft_putstr("File truncated or malformed object "
						"(load comand 0 cmdsize not a multiple of 8\n");
		if (munmap(ptr_file->ptr_free, ptr_file->size) < 0)
			return (1);
		free(ptr_file);
		return (1);
	}
	return (0);
}

int	check_fat(void *ptr, t_file_ptr *ptr_file)
{
	if (*(unsigned int*)ptr == FAT_CIGAM || *(unsigned int*)ptr == FAT_MAGIC)
	{
		ft_putstr("truncated or malformed fat file (offset plus size of cputype"
						" (18) cpusubtype (0)"
						" extends past the end of the file)\n");
		if (munmap(ptr_file->ptr_free, ptr_file->size) < 0)
			return (1);
		free(ptr_file);
		return (1);
	}
	return (0);
}
