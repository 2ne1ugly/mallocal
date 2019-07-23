/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:46:28 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 15:19:01 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

size_t	iterate_page(t_tiny *t)
{
	t_meta	*meta;
	size_t	total;
	void	*data;

	meta = (t_meta *)&t->block[0];
	total = 0;
	while (meta->cap != 0)
	{
		if (meta->cap & 1)
		{
			data = meta + 1;
			ft_printf("%p - %p : %u bytes\n",
				data, data + meta->req, meta->req);
			total += meta->req;
		}
		meta += meta->cap / ST;
	}
	return (total);
}

size_t	show_tiny()
{
	t_map_map	*m;
	t_tiny		*t;
	size_t		i;
	size_t		total;

	m = &g_mal.tiny;
	total = 0;
	while (m)
	{
		i = 0;
		while (i < m->count)
		{
			printf("TINY : %p\n", m->block[i]);
			t = m->block[i];
			total += iterate_page(t);
			i++;
		}
		m = m->next;
	}
	return (total);
}

size_t	show_small()
{
	t_map_map	*m;
	t_tiny		*t;
	size_t		i;
	size_t		total;

	m = &g_mal.small;
	total = 0;
	while (m)
	{
		i = 0;
		while (i < m->count)
		{
			printf("SMALL : %p\n", m->block[i]);
			t = m->block[i];
			total += iterate_page(t);
			i++;
		}
		m = m->next;
	}
	return (total);
}

size_t	show_large()
{
	t_map_map	*m;
	t_tiny		*t;
	size_t		i;
	size_t		total;

	m = &g_mal.large;
	total = 0;
	while (m)
	{
		i = 0;
		while (i < m->count)
		{
			printf("LARGE : %p\n", m->block[i]);
			t = m->block[i];
			total += iterate_page(t);
			i++;
		}
		m = m->next;
	}
	return (total);
}

void	show_alloc_mem()
{
	size_t	total;

	if (!g_mal.set)
		init_g_mal();
	total = show_tiny();
	total += show_small();
	total += show_large();
	ft_printf("Total : %lu bytes\n", total);
}
