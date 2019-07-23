/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:52:02 by mchi              #+#    #+#             */
/*   Updated: 2019/07/22 18:39:40 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

/*
**	skip two elements to skip **back and start_mark
*/

int		validate_meta_map(size_t *m, t_meta *meta)
{
	size_t	i;

	i = 3;
	while (m[i] != 0 && (t_meta *)&m[i] < meta)
		i += m[i] / ST;
	if ((t_meta *)&m[i] == meta)
		return (1);
	return (0);
}

int		validate_meta_map_map(t_map_map *m, t_meta *meta, size_t map_size)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		if ((void *)meta >= m->block[i] &&
			(void *)meta < m->block[i] + map_size)
			return (validate_meta_map(m->block[i], meta));
		i++;
	}
	if (m->next)
		return (validate_meta_map_map(m->next, meta, map_size));
	return (0);
}

/*
**	block size for large is 4 because only 1 meta needs to be checked.
*/

int		validate_meta(t_meta *meta)
{
	if (align((size_t)meta, ST) != (size_t)meta)
		return (0);
	if (validate_meta_map_map(&g_mal.tiny, meta, T_MAP_SIZE) ||
		validate_meta_map_map(&g_mal.small, meta, S_MAP_SIZE) ||
		validate_meta_map_map(&g_mal.large, meta, ST * 4))
		return (1);
	return (0);
}
