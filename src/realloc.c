/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:32:47 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 14:41:46 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void	*realloc_pass(t_meta *header, size_t size)
{
	t_meta	*footer;

	header->req = size;
	footer = (void *)header + header->cap - sizeof(t_meta);
	footer->req = size;
	return ((void *)header  + sizeof(t_meta));
}

void 	*realloc(void *ptr, size_t size)
{
	t_meta	*meta;
	void	*new;

	if (!g_mal.set)
		init_g_mal();
	if ((size_t)ptr < sizeof(t_meta))
		return (NULL);
	meta = ptr - sizeof(t_meta);
	if (!validate_meta(meta) || !(meta->cap & 1))
		return (NULL);
	if (meta->cap - sizeof(t_meta) * 2 <= size)
		return (realloc_pass(meta, size));
	if (meta->cap - 1 > S_BUFF_CAP)
		unmap_large(meta);
	else
	{
		free_buffer(meta);
		defrag_meta(meta);
	}
	if (!(new = malloc(size)))
		return (NULL);
	return (ft_memcpy(new, ptr, meta->req));
}
