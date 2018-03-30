/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:52:32 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/23 16:52:34 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

static void			treatment(struct segment_command *segment,
								char *ptr, char *file, int lib)
{
	t_section			*section;
	int					j;

	section = (struct section*)((void*)segment + sizeof(*segment));
	j = -1;
	if (segment->cmd == LC_SEGMENT)
	{
		while (++j < (int)segment->nsects)
		{
			if (!ft_strcmp(section[j].sectname, SECT_TEXT))
				print_hex(ptr, &section[j], file, lib);
		}
	}
	segment = (void *)segment + segment->cmdsize;
}

static void			treatment_data(struct segment_command *segment,
									char *ptr, char *file, int lib)
{
	t_section			*section;
	int					j;

	section = (struct section*)((void*)segment + sizeof(*segment));
	j = -1;
	if (segment->cmd == LC_SEGMENT)
	{
		while (++j < (int)segment->nsects)
		{
			if (!ft_strcmp(section[j].sectname, SECT_DATA))
				print_hex_data(ptr, &section[j], file, lib);
		}
	}
	segment = (void *)segment + segment->cmdsize;
}

int					ft_handle32(t_mach_header *header, t_file_ptr *ptr_file,
								char *file, int lib)
{
	int						i;
	struct load_command		*lc;

	i = -1;
	lc = (void *)ptr_file->ptr + sizeof(*header);
	while (++i < (int)header->ncmds)
	{
		treatment((struct segment_command*)lc, ptr_file->ptr, file, lib);
		lc = (void *)lc + lc->cmdsize;
		if (ptr_file->options->flag_d == TRUE)
		{
			i = 0;
			lc = (void *)ptr_file->ptr + sizeof(struct mach_header);
			while (i++ < (int)header->ncmds)
			{
				treatment_data((struct segment_command*)lc, ptr_file->ptr,
							file, -1);
				lc = (void *)lc + lc->cmdsize;
			}
		}
		if (check_ptr(lc, "extends past the end of the file\n", ptr_file) == 1)
			return (1);
	}
	return (0);
}
