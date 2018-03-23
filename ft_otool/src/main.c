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

#include "otool.h"

void	otool(char *ptr, char *name, int size)
{
	int		magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == (int)MH_MAGIC_64)
		handle_64(ptr, name, 0);
	else if (magic_number == (int)MH_MAGIC)
		handle(ptr, name, 0);
	else if (magic_number == (int)FAT_CIGAM || magic_number == (int)FAT_MAGIC)
		fat(ptr, (struct fat_header*)ptr, name);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr, name, size);
	else
		ft_error_object(name);
}

int		main(int ac, char **av)
{
	int				fd;
	struct stat		buf;
	char			*ptr;
	int				i;
	unsigned int	flag;

	if ((i = ft_flags(av)) == -1)
		return (-1);
	flag = get_flags(0);
	while (i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
		{
			ft_error_open(av[0], av[i++]);
			continue;
		}
		if (fstat(fd, &buf) < 0 || (ptr = mmap(0, buf.st_size, PROT_READ,
						MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			ft_error_object(av[i++]);
		else
			otool(ptr, av[i++], buf.st_size);
		if (munmap(ptr, buf.st_size) < 0)
			return (-1);
	}
	return (0);
}
