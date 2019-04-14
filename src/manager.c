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

t_page	*find_elem_in_map(t_page *map, size_t map_size, void *ptr)
{
	size_t	i;
	size_t	max_element;

	i = 0;
	max_element = map_size / sizeof(t_page);
	while (i < max_element - 1 && map[i].addr != ptr)
		i++;
	if (i == max_element - 1)
	{
		if (map[i].addr == NULL)
		{
			if (ptr != NULL)
				return (NULL);
			if (!(map[i].addr = new_map(g_page_size * 2)))
				return (0);
			map[i].size = g_page_size * 2;
			ft_bzero(map[i].addr, g_page_size * 2);
			return (&map[i]);
		}
		return (find_elem_in_map(map[i].addr, g_page_size * 2, ptr));
	}
	return (&map[i]);
}

t_block	find_block_in_page(char *page, size_t map_size, void *ptr)
{
	size_t	i;
	t_block block;

	i = sizeof(size_t);
	while (i < map_size)
	{
		if (ptr == (void *)&page[i])
		{
			block.block = (void **)&page[i];
			block.size_part = (size_t *)&page[i - sizeof(size_t)];
			block.parent.addr = page;
			block.parent.size = map_size;
			return (block);
		}
		i += *(size_t *)&page[i - sizeof(size_t)];
	}
	block.block = 0;
	return (block);
}

t_block	find_addr_in_map(t_page *map, size_t map_size, void *ptr)
{
	size_t	i;
	size_t	max_element;
	t_block	block;

	i = 0;
	max_element = map_size / sizeof(t_page);
	while (i < max_element - 1)
	{
		if (map[i].addr != NULL)
		{
			block = find_block_in_page(map[i].addr, map[i].size, ptr);
			if (block.block != NULL)
				return (block);
		}
		i++;
	}
	return (block);
}

t_block	find_free_memory_in_page(char *page, size_t map_size, size_t request)
{
	size_t	i;
	size_t	j;
	t_block block;

	i = 0;
	while (i < map_size - request - sizeof(size_t))
	{
		if (*(size_t *)&page[i] == 0)
		{
			j = 0;
			while(page[i + sizeof(size_t) + j] == 0)
			{
				j++;
				if (request == j)
				{
					block.block = (void **)&page[i + sizeof(size_t)];
					block.size_part = (size_t *)&page[i];
					block.parent.addr = page;
					block.parent.size = map_size;
					return (block);
				}
			}
			i++;
		}
		else
			i += *(size_t *)&page[i] + sizeof(size_t);
	}
	block.block = 0;
	return (block);
}

t_block find_free_memory(t_page *map, size_t map_size, size_t request)
{
	size_t	i;
	size_t	max_element;
	t_block	block;
	t_page	*page;

	i = 0;
	max_element = map_size / sizeof(t_page);
	block.block = NULL;
	while (i < max_element - 1)
	{
		if (map[i].addr != NULL)
		{
			block =
				find_free_memory_in_page(map[i].addr, map[i].size, request);
			if (block.block != NULL)
				return (block);
		}
		i++;
	}
	page = find_elem_in_map(map, map_size, NULL);
	page->size = g_page_size * 2;
	page->addr = new_map(g_page_size * 2);
	if (page->addr == NULL)
		return (block);
	block.size_part = page->addr;
	block.block = page->addr + sizeof(size_t);
	return (block);
}
