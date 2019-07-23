/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:40:50 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 15:33:35 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void		*find_tiny_free(t_tiny *t, size_t size)
{
	t_meta	*meta;
	size_t	i;

	i = 0;
	while (i < T_BLOCK_SIZE / ST)
	{
		meta = (t_meta *)&t->block[i];
		if (!(meta->cap & 1) && size + sizeof(t_meta) * 2 <= meta->cap)
			if (is_capable(meta, size))
				return aquire_buffer(meta, size, size);
		i += meta->cap / ST;
	}
	return (NULL);
}

void		*tiny_malloc(t_map_map *m, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	while (i < m->count)
	{
		if ((ptr = find_tiny_free(m->block[i], size)))
			return (ptr);
		i++;
	}
	if (i < MAP_MAP_SIZE / ST - 4)
	{
		m->block[i] = new_map(T_MAP_SIZE);
		if (!m->block[i])
			return (NULL);
		m->count++;
		((t_tiny *)m->block[i])->back = (t_tiny **)&m->block[i];
		return find_tiny_free(m->block[i], size);
	}
	if (m->next)
		return tiny_malloc(m->next, size);
	m->next = new_empty_map(MAP_MAP_SIZE);
	if (!m->next)
		return (NULL);
	return tiny_malloc(m->next, size);
}
