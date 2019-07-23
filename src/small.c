/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:06:37 by mchi              #+#    #+#             */
/*   Updated: 2019/07/22 19:28:40 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void	*find_small_free(t_small *s, size_t size)
{
	t_meta	*meta;
	size_t	i;

	i = 0;
	while (i < S_BLOCK_SIZE / ST)
	{
		meta = (t_meta *)&s->block[i];
		if (!(meta->cap & 1) && size + sizeof(t_meta) * 2 <= meta->cap)
			if (is_capable(meta, size))
				return aquire_buffer(meta, size);
		i += meta->cap / ST;
	}
	return (NULL);
}

void	*small_malloc(t_map_map *m, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	while (i < m->count)
	{
		if ((ptr = find_small_free(m->block[i], size)))
			return (ptr);
		i++;
	}
	if (i < MAP_MAP_SIZE / ST - 4)
	{
		m->block[i] = new_map(S_MAP_SIZE);
		if (!m->block[i])
			return (NULL);
		m->count++;
		((t_small *)m->block[i])->back = (t_small **)&m->block[i];
		return find_small_free(m->block[i], size);
	}
	if (m->next)
		return small_malloc(m->next, size);
	m->next = new_empty_map(MAP_MAP_SIZE);
	if (!m->next)
		return (NULL);
	return small_malloc(m->next, size);
}
