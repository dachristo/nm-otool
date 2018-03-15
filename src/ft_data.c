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

void	ft_sym32(struct symtab_command *sym, char **sec_str, t_file_ptr *ptr_file)
{
	int				i;
	char			*stringtable;
	struct nlist	*array;
	int				*index;
	t_data32		data;

	array = (void *)ptr_file->ptr + sym->symoff;
	stringtable = (void *)ptr_file->ptr + sym->stroff;
	check_ptr(array, "ar truncated or malformed object (load comamnds extend past the end of the file)\n", ptr_file);
	check_ptr(stringtable, "ar truncated or malformed object (load comamnds extend past the end of the file)\n", ptr_file);
	if ((index = malloc(sizeof(int) * sym->nsyms)) == NULL)
		return ;
	i = -1;
	while (++i < (int)sym->nsyms)
		index[i] = i;
	data.array = array;
	data.index = index;
	data.stringtable = stringtable;
//	if (!(ft_options(0, NULL, NULL) & FLAG_P))
		ft_sort32(&data, 0, sym->nsyms - 1);
	ft_print_out32(&data, sec_str, sym->nsyms);
	free(index);
}

void	ft_sym64(struct symtab_command *sym, char **sec_str, t_file_ptr *ptr_file)
{
	int				i;
	char			*stringtable;
	struct nlist_64 *array;
	int				*index;
	t_data			data;

	array = (void *)ptr_file->ptr + sym->symoff;
	stringtable = (void *)ptr_file->ptr + sym->stroff;
	check_ptr(array, "ar truncated or malformed object (load comamnds extend past the end of the file)\n", ptr_file);
	check_ptr(stringtable, "ar truncated or malformed object (load comamnds extend past the end of the file)\n", ptr_file);
	if ((index = malloc(sizeof(int) * sym->nsyms)) == NULL)
		return ;
	i = -1;
	while (++i < (int)sym->nsyms)
		index[i] = i;
	data.array = array;
	data.index = index;
	data.stringtable = stringtable;
 	if (ptr_file->options->flag_p != TRUE)
		ft_sort64(&data, 0, sym->nsyms - 1);
	ft_print_out64(&data, sec_str, sym->nsyms);
	free(index);
}
