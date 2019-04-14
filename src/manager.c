/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:05:34 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 16:49:48 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_tiny_slab		*find_tiny_free_block(size_t request)
{
	size_t		i;
	size_t		elem_size;
	t_tiny_slab	*curr_map;

	elem_size = (g_page_size * 4) / sizeof(t_tiny_slab);
	curr_map = g_tiny_map;
	i = 1;
	while (1)
	{
		if (curr_map[i].size == ~4)
		{
			if (curr_map[i].data[0] == NULL)
				if (!(curr_map[i].data[0] = new_map()))
					return (NULL);
			curr_map = (void *)curr_map[i].data[0];
			i = 1;
		}
		if (!(curr_map[i].size & 1L) &&
			(curr_map[i].size & ~1L) - sizeof(size_t) >= request)
			return (&curr_map[i]);
		i += (curr_map[i].size & ~1L) / sizeof(t_tiny_slab);
	}
}

t_small_slab	*find_small_free_block(size_t request)
{
	size_t			i;
	t_small_slab	*curr_map;

	curr_map = g_small_map;
	i = 1;
	while (1)
	{
		if (curr_map[i].size == ~4)
		{
			if (curr_map[i].data[0] == NULL)
				if (!(curr_map[i].data[0] = new_map()))
					return (NULL);
			curr_map = (void *)curr_map[i].data[0];
			i = 1;
		}
		if (!(curr_map[i].size & 1L) &&
			(curr_map[i].size & ~1L) - sizeof(size_t) >= request)
			return (&curr_map[i]);
		i += (curr_map[i].size & ~1L) / sizeof(t_small_slab);
	}
}

void			delete_addr(void	*ptr)
{
	size_t		i;
	size_t		elem_size;
	size_t		*curr_map;

	curr_map = g_large_map;
	i = 0;
	elem_size = (g_page_size * 4) / sizeof(size_t);
	while (1)
	{
		if (i == elem_size - 1)
		{
			if (curr_map[i] == NULL)
			{
				printf("major error!!! NOOO");
				exit(1);
			}
			curr_map = curr_map[i];
			i = 0;
		}
		if (curr_map[i] == ptr)
		{
			curr_map[i] = NULL;
			return ;
		}
		i++;
	}
}

