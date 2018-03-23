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
# define TRUE 1
# define FALSE 0
# define T_SEG_CMD_64 struct segment_command_64
# define T_SEC_64 struct section_64
# define T_FAT_HEADER struct fat_header
# define T_FAT_ARCH struct fat_arch

typedef struct		s_sort
{
	int				c1;
	int				c2;
	int				*index2;
}					t_sort;

typedef struct		s_options
{
	int				flag_d;
	int				flag_f;
	int				n;
}					t_options;

typedef struct		s_file_ptr
{
	void			*ptr_free;
	void			*ptr;
	void			*ptr_end;
	int				size;
	t_options		*options;
}					t_file_ptr;

typedef struct		s_data
{
    struct nlist_64	*array;
    char			*stringtable;
    int             *index;
	t_file_ptr		*ptr_file;
}					t_data;

typedef struct		s_data32
{
	struct nlist	*array;
	char			*stringtable;
	int				*index;
	t_file_ptr		*ptr_file;
}					t_data32;



typedef struct		s_lib
{
	char			*start;
	unsigned int	st_len;
	unsigned int	arr_len;
	char			*str;
}					t_lib;

typedef struct mach_header_64	t_mach_header_64;
typedef struct mach_header		t_mach_header;
typedef struct fat_header		t_fat_header;
/*typedef struct nlist_64			t_nlist_64;
typedef struct nlist			t_nlist;*/

typedef struct section	t_section;

/*
 * LIBFT
 */
void			ft_putstr(char *str);
void			ft_putstr_fd(char *str, int fd);
void 			ft_putchar(char c);
void			ft_putnbr(long n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_puthex(size_t n);
void			ft_puthex2(size_t n);
int				ft_puthex_nb(size_t n, int i);
char			*ft_strchr(const char *s, int c);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);

/*
 * UTIL CHECK
 */
int				check_file(char *file, t_options *options);
int				check_ptr(void *ptr, char *error, t_file_ptr *file_ptr);

/*
 * MH MAGIC 64
 */
int				ft_handle64(t_mach_header_64 *header, t_file_ptr *file_ptr, char *file, int lib);

/*
 * MH MAGIC 32
 */
int				ft_handle32(t_mach_header *header, t_file_ptr *file_ptr, char *file, int lib);

/*
 * LIB
 */
int				ft_lib(t_file_ptr *ptr_file, char *file, int size);

/*
 * FAT
 */
int				ft_fat_handle(t_fat_header *header, t_file_ptr *ptr_file, char *file);

/*
 * TOOLS
 */
unsigned int	ft_rev_int(unsigned int num);
int				ft_sort_numeric(int val1, int val2, t_options *options);
int				*ft_index(int *index, int start, int end);

/*
 * ERROR
 */
void			ft_error_object(char *s);


/*
 * PRINT
 */
void			print_hex(char *ptr, struct section *section, char *name, int lib);
void			print_hex_data(char *ptr, struct section *section, char *name, int print);
void			print_head(struct section *section, char *name, int print);
void			print_hex_64(char *ptr, struct section_64 *section, char *name, int lib);
void			print_hex_data_64(char *ptr, struct section_64 *section, char *name, int print);
void			print_head_64(struct section_64 *section, char *name, int print);

#endif
