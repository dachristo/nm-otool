/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 17:06:19 by kperreau          #+#    #+#             */
/*   Updated: 2015/09/22 23:33:50 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/otool.h"

void		ft_error_object(char *s)
{
	ft_putstr_fd(s, 1);
	ft_putstr_fd(": is not an object file\n", 1);
}