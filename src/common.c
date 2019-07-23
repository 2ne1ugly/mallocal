/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:38:51 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 00:32:14 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void			init_g_mal()
{
	t_meta	*header;
	t_meta	*footer;

	g_mal.tiny.block[0] = &g_mal.tiny_prealloc;
	g_mal.tiny_prealloc.back = (t_tiny **)&g_mal.tiny.block[0];
	g_mal.tiny.count++;
	header = (t_meta *)&g_mal.tiny_prealloc.block[0];
	header->cap = T_BLOCK_SIZE;
	footer = (t_meta *)&g_mal.tiny_prealloc.block[T_BLOCK_SIZE / ST - 1];
	footer->cap = T_BLOCK_SIZE;
	g_mal.small.block[0] = &g_mal.small_prealloc;
	g_mal.tiny_prealloc.back = (t_tiny **)&g_mal.small.block[0];
	g_mal.small.count++;
	header = (t_meta *)&g_mal.small_prealloc.block[0];
	header->cap = S_BLOCK_SIZE;
	footer = (t_meta *)&g_mal.small_prealloc.block[S_BLOCK_SIZE / ST - 1];
	footer->cap = S_BLOCK_SIZE;
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
