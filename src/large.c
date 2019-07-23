/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:08:41 by mchi              #+#    #+#             */
/*   Updated: 2019/07/22 23:37:57 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void	unmap_large(t_meta *meta)
{
	t_large		*t;
	size_t		*size_t;

	t = (void *)meta - sizeof(t_meta) - ST;
	delete_map_elem((void **)t->back);
	if (munmap(t, align(meta->req + ST * 24, getpagesize())) == -1)
	{
		ft_printf("major error\n");
	}
}

void	*large_malloc(t_map_map *m, size_t size)
{
	t_large	*large;
	t_meta	*header;

	if (m->count == MAP_MAP_SIZE / ST - 3)
	{
		if (!m->next)
			m->next = new_empty_map(MAP_MAP_SIZE);
		if (!m->next)
			return (NULL);
		return (large_malloc(m->next, size));
	}
	large = new_empty_map(size + ST * 24);
	if (!large)
		return (NULL);
	m->block[m->count] = large;
	large->back = (struct s_large **)&m->block[m->count];
	header = &large->header;
	header->cap = align(size + ST * 2, getpagesize()) - ST + 1;
	header->req = size;
	m->count++;
	return (&large->data);
}

/*
**	-st is for marker
*/
