/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:41:45 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/09 14:41:47 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

static void			treatment_64(struct segment_command_64 *segment,
									char *ptr, char *file, int lib)
{
	int					j;
	struct section_64	*section;

	section = (struct section_64*)((void*)segment + sizeof(*segment));
	j = -1;
	if (segment->cmd == LC_SEGMENT_64)
	{
		while (++j < (int)segment->nsects)
		{
			if (!ft_strcmp(section[j].sectname, SECT_TEXT))
				print_hex_64(ptr, &section[j], file, lib);
		}
	}
	segment = (void *)segment + segment->cmdsize;
}

static void			treatment_64_data(struct segment_command_64 *segment,
										 char *ptr, char *file, int lib)
{
	int					j;
	struct section_64	*section;

	section = (struct section_64*)((void*)segment + sizeof(*segment));
	j = -1;
	if (segment->cmd == LC_SEGMENT_64)
	{
		while (++j < (int)segment->nsects)
		{
			if (!ft_strcmp(section[j].sectname, SECT_DATA))
				print_hex_data_64(ptr, &section[j], file, lib);
		}
	}
	segment = (void *)segment + segment->cmdsize;
}


int	ft_handle64(t_mach_header_64 *header, t_file_ptr *ptr_file, char *file, int lib)
{
	int					i;
	struct load_command	*lc;
	struct segment_command_64	*segment;

	i = -1;
	lc = (void *)ptr_file->ptr + sizeof(*header);
	while (++i < (int)header->ncmds)
	{
		segment = (struct segment_command_64*)lc;
		treatment_64(segment, ptr_file->ptr, file, lib);
		lc = (void *)lc + lc->cmdsize;
		if (ptr_file->options->flag_d == TRUE)
		{
			i = 0;
			lc = (void *)ptr_file->ptr + sizeof(struct mach_header_64);
			while (i++ < (int)header->ncmds)
			{
				segment = (struct segment_command_64*)lc;
				treatment_64_data(segment, ptr_file->ptr, file, -1);
				lc = (void *)lc + lc->cmdsize;
			}
		}
		if (check_ptr(lc, "extends past the end of the file\n", ptr_file) == 1)
			return (1);
	}
	return (1);
}
