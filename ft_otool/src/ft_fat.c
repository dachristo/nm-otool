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

#include "../include/otool.h"

static void			treatment_fat(T_SEG_CMD_64 *segment, char *ptr, char *name)
{
	int				j;
	T_SEC_64		*sect;

	sect = (struct section_64*)((void*)segment + sizeof(*segment));
	j = -1;
	if (segment->cmd == LC_SEGMENT_64)
	{
		while (++j < (int)segment->nsects)
		{
			if (!ft_strcmp(sect[j].sectname, SECT_TEXT))
				print_hex_64(ptr, &sect[j], name, 0);
		}
	}
	segment = (void *)segment + segment->cmdsize;
}

static void			treatment_data_fat(T_SEG_CMD_64 *segment, char *ptr,
										char *name)
{
	int				j;
	T_SEC_64		*sect;

	sect = (struct section_64*)((void*)segment + sizeof(*segment));
	j = -1;
	if (segment->cmd == LC_SEGMENT_64)
	{
		while (++j < (int)segment->nsects)
		{
			if (!ft_strcmp(sect[j].sectname, SECT_DATA))
				print_hex_data_64(ptr, &sect[j], name, -1);
		}
	}
	segment = (void *)segment + segment->cmdsize;
}

static void			handle_fat(t_file_ptr *ptr_file, char *ptr,
								T_FAT_HEADER *header, char *name)
{
	int							i;
	struct load_command			*lc;
	struct segment_command_64	*segment;

	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (i++ < (int)ft_rev_int(header->nfat_arch))
	{
		segment = (struct segment_command_64*)lc;
		treatment_fat(segment, ptr, name);
		lc = (void *)lc + lc->cmdsize;
	}
	if (ptr_file->options->flag_d == TRUE)
	{
		i = 0;
		lc = (void *)ptr + sizeof(struct mach_header_64);
		while (i++ < (int)ft_rev_int(header->nfat_arch) + 1)
		{
			segment = (struct segment_command_64*)lc;
			treatment_data_fat(segment, ptr, name);
			lc = (void *)lc + lc->cmdsize;
		}
	}
}

int					ft_fat_handle(t_fat_header *header,
									t_file_ptr *ptr_file, char *file)
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
		handle_fat(ptr_file, ptr_file->ptr, header, file);
	else if (!ft_strncmp(ptr_file->ptr, ARMAG, SARMAG))
		ft_lib(ptr_file, ptr_file->ptr, file, ft_rev_int(arch->size));
	else if (check_fat(ptr_file->ptr, ptr_file) == 1)
		return (1);
	return (0);
}
