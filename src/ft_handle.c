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

void	ft_handle32(char *ptr, t_mach_header *header)
{
	int					i;
	int					j;
	int					k;
	struct load_command	*lc;
	char				*sec_str[255];

	i = -1;
	j = -1;
	lc = (void *)ptr + sizeof(*header);
	while (++i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			k = -1;
			while (++k < (int)((struct segment_command*)lc)->nsects)
				sec_str[++j] = ((struct section*)((void *)lc + \
				sizeof(struct segment_command)))[k].sectname;
		}
		if (lc->cmd == LC_SYMTAB)
		{
			ft_sym32((struct symtab_command*)lc, sec_str, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	ft_handle64(char *ptr, t_mach_header_64 *header)
{
	int					i;
	int					j;
	int					k;
	struct load_command	*lc;
	char				*sec_str[255];

	i = -1;
	j = -1;
	lc = (void *)ptr + sizeof(*header);
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
			ft_sym64((struct symtab_command *)lc, sec_str, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
