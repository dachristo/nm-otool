/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:14:41 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/14 16:14:43 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

int	ft_fat_handle(t_fat_header *header, t_file_ptr *ptr_file, char *file)
{
	struct fat_arch		*arch;
	int					i;

	arch = (void*)ptr_file->ptr + sizeof(*header);
	i = -1;
	while (++i < (int)ft_rev_int(header->nfat_arch))
	{
		if (ft_rev_int(arch->cputype) == CPU_TYPE_X86_64)
			break ;
		arch = (void*)arch + sizeof(*arch);
		if (check_ptr(arch, "arch extends past the end of the file\n",
					ptr_file) == 1)
			return (1);
	}
	ptr_file->ptr = (void*)ptr_file->ptr + ft_rev_int(arch->offset);
	if (*(unsigned int*)ptr_file->ptr == MH_MAGIC_64)
		return (ft_handle64((struct mach_header_64 *)ptr_file->ptr,
							ptr_file, -1, -1));
	else if (!ft_strncmp(ptr_file->ptr, ARMAG, SARMAG))
		return (ft_lib(ptr_file, file, ft_rev_int(arch->size)));
	else if (check_fat(ptr_file->ptr, ptr_file) == 1)
		return (1);
	return (0);
}
