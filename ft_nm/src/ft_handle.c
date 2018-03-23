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

#include "../include/nm_otool.h"

int	ft_handle32(t_mach_header *header, t_file_ptr *ptr_file, int i, int j)
{
	int					k;
	struct load_command	*lc;
	char				*sec_str[255];

	lc = (void *)ptr_file->ptr + sizeof(*header);
	while (++i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			k = -1;
			while (++k < (int)((struct segment_command *)lc)->nsects)
				sec_str[++j] = ((struct section *)((void *)lc + \
				sizeof(struct segment_command)))[k].sectname;
		}
		if (lc->cmd == LC_SYMTAB)
		{
			if (ft_sym32((struct symtab_command*)lc, sec_str, ptr_file) == 1)
				return (1);
			return (0);
		}
		lc = (void *)lc + lc->cmdsize;
		if (check_ptr(lc, "extends past the end of the file\n", ptr_file) == 1)
			return (1);
	}
	return (0);
}

int	ft_handle64(t_mach_header_64 *header, t_file_ptr *ptr_file,
					int i, int j)
{
	int					k;
	struct load_command	*lc;
	char				*sec_str[255];

	lc = (void *)ptr_file->ptr + sizeof(*header);
	while (++i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			k = -1;
			while (++k < (int)((struct segment_command_64 *)lc)->nsects)
				sec_str[++j] = ((struct section_64 *)((void *)lc + \
				sizeof(struct segment_command_64)))[k].sectname;
		}
		if (lc->cmd == LC_SYMTAB)
		{
			if (ft_sym64((struct symtab_command *)lc, sec_str, ptr_file) == 1)
				return (1);
			return (0);
		}
		lc = (void *)lc + lc->cmdsize;
		if (check_ptr(lc, "extends past the end of the file\n", ptr_file) == 1)
			return (1);
	}
	return (1);
}
