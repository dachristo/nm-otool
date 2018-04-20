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

static int		treatment_64(struct segment_command_64 *segment,
									t_file_ptr *ptr_file, char *file, int lib)
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
				print_hex_64(ptr_file->ptr, &section[j], file, lib);
		}
	}
	segment = (void *)segment + segment->cmdsize;
	if (check_ptr(segment, "extends past the end of the file\n", ptr_file) == 1)
		return (1);
	return (0);
}

static int		treatment_64_data(struct segment_command_64 *segment,
									t_file_ptr *ptr_file, char *file, int lib)
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
				print_hex_data_64(ptr_file->ptr, &section[j], file, lib);
		}
	}
	segment = (void *)segment + segment->cmdsize;
	if (check_ptr(segment, "extends past the end of the file\n", ptr_file) == 1)
		return (1);
	return (0);
}

static int		handle_flag_d(struct load_command	*lc, t_file_ptr *ptr_file,
								t_mach_header_64 *header, char *file)
{
	int i;

	i = 0;
	lc = (void *)ptr_file->ptr + sizeof(struct mach_header_64);
	while (i++ < (int)header->ncmds)
	{
		if (treatment_64_data((struct segment_command_64*)lc, ptr_file,
							file, -1) == 1)
			return (1);
		lc = (void *)lc + lc->cmdsize;
		if (check_ptr(lc, "extends past the end of the file\n", ptr_file) == 1)
			return (1);
	}
	return (0);
}

int				ft_handle64(t_mach_header_64 *header, t_file_ptr *ptr_file,
								char *file, int lib)
{
	int					i;
	struct load_command	*lc;

	i = -1;
	lc = (void *)ptr_file->ptr + sizeof(*header);
	while (++i < (int)header->ncmds)
	{
		if (treatment_64((struct segment_command_64*)lc, ptr_file,
						file, lib) == 1)
			return (1);
		lc = (void *)lc + lc->cmdsize;
		if (ptr_file->options->flag_d == TRUE)
		{
			if (handle_flag_d(lc, ptr_file, header, file) == 1)
				return (1);
		}
		if (check_ptr(lc, "extends past the end of the file\n",
					ptr_file) == 1 ||
			(check_lc(lc->cmdsize, i, (int)header->ncmds, ptr_file) == 1))
			return (1);
	}
	return (0);
}
