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

size_t	*find_free_block(size_t *map, size_t request)
{
	size_t	i;

	i = 2;
	while (1)
	{
		if (map[i] == ~4L)
		{
			if (map[i + 1] == NULL)
				map[i + 1] = new_map(map, g_page_size * 4);
			if (map[i + 1] == NULL)
				return (NULL);
			map = map[i + 1];
			i = 2;
		}
		if (is_free_header(&map[i]) && map[i] - 3 * sizeof(size_t) >= request)
			return (&map[i]);
		i += lowest_multiple(sizeof(size_t), map[i]) / sizeof(size_t);
	}
}

size_t	*find_addr_space(void)
{
	size_t	i;
	size_t	*curr_map;

	i = 2;
	curr_map = g_large_map;
	while (1)
	{
		if (curr_map[i] == ~4L)
		{
			if (curr_map[i + 1] == NULL)
				curr_map[i + 1] = new_map(curr_map, g_page_size * 4);
			if (curr_map[i + 1] == NULL)
				return (NULL);
			curr_map = curr_map[i + 1];
			i = 2;
		}
		if (curr_map[i] == 0)
			return (&curr_map[i]);
		i++;
	}
}

void	free_the_block(size_t *block)
{
	size_t	mem_count;

	mem_count = lowest_multiple(sizeof(size_t), *block);
	block[0] = mem_count;
	block[mem_count / sizeof(size_t) - 1] = mem_count;
	block[mem_count / sizeof(size_t) - 2] = 0;
}

void	defrag_free_block(size_t *block)
{
	size_t	mem_count;

	mem_count = *block;
	if (is_free_header(&block[mem_count / sizeof(size_t)]))
		mem_count += block[mem_count / sizeof(size_t)];
	if (is_free_footer(&block[-1]))
	{
		block[-block[-1]] = block[-1] + mem_count;
		block[mem_count - 1] = block[-1] + mem_count;
	}
	else
	{
		block[0] = mem_count;
		block[mem_count - 1] = mem_count;
	}
}

size_t	*alloc_free_block(size_t *block, size_t request)
{
	size_t	i;
	size_t	left_over;
	size_t	next_header;
	size_t	next_next_header;

	next_header = lowest_multiple(sizeof(size_t), *block) / sizeof(size_t);
	left_over = *block - lowest_multiple(sizeof(size_t), *block);
	*block = request;
	block[next_header - 1] = request;
	block[next_header - 2] = 1;
	if (left_over > 0)
	{
		block[next_header] = left_over;
		next_next_header = next_header +
			lowest_multiple(8, left_over) / sizeof(size_t);
		block[next_next_header - 1] = left_over;
		block[next_next_header - 2] = 0;
	}
	return (block + sizeof(size_t));
}
