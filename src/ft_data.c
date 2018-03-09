/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:44:39 by dchristo          #+#    #+#             */
/*   Updated: 2018/03/09 14:44:40 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_otool.h"

void	ft_sym32(struct symtab_command *sym, char **sec_str, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist	*array;
	int				*index;
	t_data32		data;

	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	if ((index = malloc(sizeof(int) * sym->nsyms)) == NULL)
		return ;
	i = -1;
	while (++i < (int)sym->nsyms)
		index[i] = i;
	data.array = array;
	data.index = index;
	data.stringtable = stringtable;
	free(index);
//	if (!(ft_options(0, NULL, NULL) & FLAG_P))
		ft_sort32(&data, sym->nsyms);
	ft_print_out32(&data, sec_str, sym->nsyms);
}

void	ft_sym64(struct symtab_command *sym, char **sec_str, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64 *array;
	int				*index;
	t_data			data;

	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	if ((index = malloc(sizeof(int) * sym->nsyms)) == NULL)
		return ;
	i = -1;
	while (++i < (int)sym->nsyms)
		index[i] = i;
	data.array = array;
	data.index = index;
	data.stringtable = stringtable;
	free(index);
//	if (!(ft_options(0, NULL, NULL) & FLAG_P))
		ft_sort64(&data, sym->nsyms);
	ft_print_out64(&data, sec_str, sym->nsyms);
}
