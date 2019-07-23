/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:38:51 by mchi              #+#    #+#             */
/*   Updated: 2019/07/22 20:57:46 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void			init_g_mal()
{
	g_mal.set = 1;
}

void			delete_map_elem(void **elem)
{
	long	i;

	i = 1;
	*elem = NULL;
	while (elem[i] != 0)
	{
		*(size_t *)elem[i] = (size_t)&elem[i - 1];
		elem[i - 1] = elem[i];
		elem[i] = 0;
		i++;
	}
	i = 1;
	while (elem[-i] != 0)
		i++;
	i++;
	elem[-i]--;
}

/*
**	align to m
*/

inline size_t	align(size_t n, size_t m)
{
	if (n % m == 0)
		return (n);
	return (n + (m - n % m));
}
