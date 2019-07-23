/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:56:42 by mchi              #+#    #+#             */
/*   Updated: 2019/07/22 19:23:42 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

int				is_capable(t_meta *meta, size_t size)
{
	size_t	need;

	if (meta->cap & 1)
		return (0);
	need = align(size, ST) + sizeof(t_meta) * 2;
	if (meta->cap == need)
		return (1);
	if (meta->cap >= need + sizeof(t_meta) * 2)
		return (1);
	return (0);
}

void			*aquire_buffer(t_meta *header, size_t size)
{
	size_t	need;
	size_t	left;
	t_meta	*footer;
	t_meta	*next_header;
	t_meta	*next_footer;

	need = align(size, ST) + sizeof(t_meta) * 2;
	footer = (void *)header + need - sizeof(t_meta);
	footer->cap = need + 1;
	footer->req = size;
	if (header->cap != need)
	{
		left = header->cap - need;
		next_header = (void *)footer + sizeof(t_meta);
		next_footer = (void *)next_header + left - sizeof(t_meta);
		next_header->cap = left;
		next_header->req = 0;
		*next_footer = *next_header;
	}
	*header = *footer;
	return ((void *)header + sizeof(t_meta));
}

void			*new_empty_map(size_t size)
{
	void	*map;

	map = mmap(NULL, align(size, getpagesize()), PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (map == MAP_FAILED)
		map = NULL;
	memset(map, 0, size);
	return (map);
}

void			*new_map(size_t size)
{
	size_t	*map;

	map = new_empty_map(size);
	map[3] = size - ST * 4;
	map[size / ST - 4] = size - ST * 4;
	return (map);
}

void			*malloc(size_t size)
{
	if (!g_mal.set)
		init_g_mal();
	if (size < T_BUFF_CAP - sizeof(t_meta) * 2)
		return (tiny_malloc(&g_mal.tiny, size));
	if (size < S_BUFF_CAP - sizeof(t_meta) * 2)
		return (small_malloc(&g_mal.small, size));
	return (large_malloc(&g_mal.large, size));
}
