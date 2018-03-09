/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:40:38 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/31 18:15:14 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <stdio.h>
#include <errno.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include </usr/include/ar.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# define FT_HEX "abcdef"

typedef struct	s_data
{
    struct nlist_64	*array;
    char			*stringtable;
    int             *index;
}				t_data;

typedef struct	s_data32
{
	struct nlist	*array;
	char			*stringtable;
	int				*index;
}				t_data32;

typedef struct mach_header_64	t_mach_header_64;
typedef struct mach_header		t_mach_header;
typedef struct fat_header		t_fat_header;
typedef struct nlist_64			t_nlist_64;
typedef struct nlist			t_nlist;

/*
 * LIBFT
 */
void	ft_putstr(char *str);
void 	ft_putchar(char c);
void	ft_putnbr(long n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_puthex(size_t n);

/*
 * UTIL CHECK
 */
int		check_file(char *file, int argc);

/*
 * MH MAGIC 64
 */
void	ft_handle64(char *ptr, t_mach_header_64 *header);
void	ft_sym64(struct symtab_command *sym, char **sec_str, char *ptr);
void	ft_print_out64(t_data *data, char **sec_str, int n);
void	ft_sort32(t_data32 *data, int nsyms);

/*
 * MH MAGIC 32
 */
void	ft_handle32(char *ptr, t_mach_header *header);
void	ft_sym32(struct symtab_command *sym, char **sec_str, char *ptr);
void	ft_print_out32(t_data32 *data, char **sec_str, int n);
void	ft_sort64(t_data *data, int nsyms);

#endif
