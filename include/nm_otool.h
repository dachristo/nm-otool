/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:40:38 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/25 15:25:35 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# define FT_HEX "abcdef"

void	nm(char *str);
void	ft_putstr(char *str);
void	ft_putnbr(long n);
int		start_nm(char *file);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_puthex(size_t n);

#endif
