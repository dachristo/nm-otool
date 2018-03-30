/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:43:27 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/14 16:43:28 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

static void		ft_sub_lib(t_file_ptr *ptr_file)
{
	if (*(unsigned int*)ptr_file->ptr == MH_MAGIC_64)
		ft_handle64((struct mach_header_64 *)ptr_file->ptr,
					ptr_file->ptr, ptr_file->ptr, 1);
	else
		ft_handle32((struct mach_header *)ptr_file->ptr,
					ptr_file->ptr, ptr_file->ptr, 1);
}

void			ft_lib(t_file_ptr *ptr_file, char *ptr,
						char *file, int size)
{
	struct ranlib	*lib;
	struct ar_hdr	*ar;
	int				i;
	t_lib			slib;

	slib.start = (void*)ptr + sizeof(struct ar_hdr) + SARMAG + 20;
	slib.st_len = *(unsigned int*)slib.start / sizeof(struct ranlib);
	lib = (struct ranlib*)(slib.start + 4);
	ptr_file->ptr = (void*)lib + slib.st_len * sizeof(struct ranlib) + 4;
	slib.arr_len = *(unsigned int*)(ptr_file->ptr - 4);
	ptr_file->ptr += slib.arr_len;
	i = -1;
	printf("Archive : %s\n", file);
	while (++i < (int)slib.arr_len && (char *)ptr_file->ptr - ptr < size)
	{
		ar = (struct ar_hdr*)ptr_file->ptr;
		ptr_file->ptr += sizeof(struct ar_hdr);
		printf("%s(%s):\n", file, ptr_file->ptr);
		ptr_file->ptr += ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
		ft_sub_lib(ptr_file->ptr);
		ptr_file->ptr += ft_atoi(ar->ar_size) -
				ft_atoi(ft_strchr(ar->ar_name, '/')\
			+ 1);
	}
}
