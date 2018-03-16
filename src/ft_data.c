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

int	ft_check_ptr(struct nlist *array, char *stringtable, char *error,
					t_file_ptr *ptr_file)
{
	if (check_ptr(array, error, ptr_file) == 1)
		return (1);
	if (check_ptr(stringtable, error, ptr_file) == 1)
		return (1);
	return (0);
}

int	ft_check_ptr64(struct nlist_64 *array, char *stringtable, char *error,
					t_file_ptr *ptr_file)
{
	if (check_ptr(array, error, ptr_file) == 1)
		return (1);
	if (check_ptr(stringtable, error, ptr_file) == 1)
		return (1);
	return (0);
}

int	ft_sym32(struct symtab_command *sym, char **sec_str,
				t_file_ptr *ptr_file)
{
	int				i;
	char			*stringtable;
	struct nlist	*array;
	int				*index;
	t_data32		data;

	array = (void *)ptr_file->ptr + sym->symoff;
	stringtable = (void *)ptr_file->ptr + sym->stroff;
	if (ft_check_ptr(array, stringtable, "ar truncated or malformed object "
			"(load comamnds extend past the end of the file)\n", ptr_file) == 1)
		return (1);
	if ((index = malloc(sizeof(int) * sym->nsyms)) == NULL)
		return (1);
	i = -1;
	while (++i < (int)sym->nsyms)
		index[i] = i;
	data.array = array;
	data.index = index;
	data.stringtable = stringtable;
	data.ptr_file = ptr_file;
	if (ptr_file->options->flag_p != TRUE)
		ft_sort32(&data, 0, sym->nsyms - 1);
	ft_print_out32(&data, sec_str, sym->nsyms);
	free(index);
	return (0);
}

int	ft_sym64(struct symtab_command *sym, char **sec_str,
				t_file_ptr *ptr_file)
{
	int				i;
	char			*stringtable;
	struct nlist_64 *array;
	int				*index;
	t_data			data;

	array = (void *)ptr_file->ptr + sym->symoff;
	stringtable = (void *)ptr_file->ptr + sym->stroff;
	if (ft_check_ptr64(array, stringtable, "ar truncated or malformed object "
			"(load comamnds extend past the end of the file)\n", ptr_file) == 1)
		return (1);
	if ((index = malloc(sizeof(int) * sym->nsyms)) == NULL)
		return (1);
	i = -1;
	while (++i < (int)sym->nsyms)
		index[i] = i;
	data.array = array;
	data.index = index;
	data.stringtable = stringtable;
	data.ptr_file = ptr_file;
	if (ptr_file->options->flag_p != TRUE)
		ft_sort64(&data, 0, sym->nsyms - 1);
	ft_print_out64(&data, sec_str, sym->nsyms);
	free(index);
	return (0);
}
