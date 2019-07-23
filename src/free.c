/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:29:05 by mchi              #+#    #+#             */
/*   Updated: 2019/07/22 21:20:35 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void	free_buffer(t_meta *header)
{
	t_meta	*footer;

	header->cap -= 1;
	footer = (void *)header + header->cap - sizeof(t_meta);
	footer->cap -= 1;
}

void	unmap_if_alone(t_meta *header, t_meta *footer)
{
	t_tiny		*m;
	size_t		size;

	if ((header - 1)->cap == 0 && (footer + 1)->cap == 0)
	{
		m = (void *)header - ST - sizeof(t_meta);
		delete_map_elem((void **)m->back);
		size = align(T_MAP_SIZE, getpagesize());
		if (header->cap > T_MAP_SIZE)
			size = align(S_MAP_SIZE, getpagesize());
		if (munmap(m, size) == -1)
		{
			ft_printf("major error\n");
		}
	}
}

void	defrag_meta(t_meta *meta)
{
	t_meta	*total_header;
	t_meta	*total_footer;
	t_meta	*next_header;
	t_meta	*prev_footer;
	size_t	total_bytes;

	total_bytes = meta->cap;
	next_header = (void *)meta + meta->cap;
	total_footer = (void *)next_header - sizeof(t_meta);
	if (!(next_header->cap & 1))
	{
		total_bytes += next_header->cap;
		total_footer = (void *)next_header + next_header->cap - sizeof(t_meta);
	}
	prev_footer = (void *)meta - sizeof(t_meta);
	total_header = meta;
	if (!(prev_footer->cap & 1))
	{
		total_bytes += prev_footer->cap;
		total_header = (void *)prev_footer - prev_footer->cap + sizeof(t_meta);  
	}
	total_header->cap = total_bytes;
	total_footer->cap = total_bytes;
	//unmap_if_alone(total_header, total_footer);
}

void	free(void *ptr)
{
	t_meta	*meta;

	if (!g_mal.set)
		init_g_mal();
	if ((size_t)ptr < sizeof(t_meta))
		return ;
	meta = ptr - sizeof(t_meta);
	if (!validate_meta(meta))
	{
		ft_printf("invalid free\n");
		return ;
	}
	if (!(meta->cap & 1))
	{
		ft_printf("free on non allocated\n");
		return ;
	}
	if (meta->cap - 1 > S_BUFF_CAP)
		unmap_large(meta);
	else
	{
		free_buffer(meta);
		defrag_meta(meta);
	}
}
