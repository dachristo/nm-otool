/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:41:43 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/24 16:08:28 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm-otool.h"

void	nm(char *str)
{
	(void)str;
	ft_putstr("in nm\n");	
}

int		start_nm(char *file)
{
	int			fd;
	struct stat buf;
	char 		*ptr;

	if ((fd = open(file, O_RDONLY)) < 0 ) 
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
		return(EXIT_FAILURE);
	}
	nm(ptr);
	return (EXIT_SUCCESS);
}

