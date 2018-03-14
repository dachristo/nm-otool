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

#include "../include/nm_otool.h"

void	check_ptr(void *ptr, char *error, t_file_ptr *ptr_file)
{
	if (ptr > ptr_file->ptr_end)
	{
		ft_putstr(error);
		if (munmap(ptr_file->ptr_free, ptr_file->size) < 0)
		{
			printf("fail\n");
			exit(1);
		}
		free(ptr_file);
		exit(1);
	}
}