/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:40:52 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/23 18:45:49 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm-otool.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("pas d'argument\n");
		return (0);
	}
	(void)argv;
	nm();
	otool();
	return (0);
}
