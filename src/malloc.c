/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:11:37 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 16:49:11 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//first sizeof(size_t) will be the size of the array. size_t
//my malloc only works til 500 MB!... i think?
//for now, what it does is using tons of pages.

void	*malloc(size_t size)
{
	size_t	request_size;
	t_block	block;
	void	*mem;
	t_page	*empty_page;

	if (!check_minor())
		return (NULL);
	if (size > LARGE)
	{
		request_size = lowest_multiple(g_page_size, size + sizeof(size_t));
		if (!(mem = new_map(g_page_size)))
			return (0);
		empty_page = find_elem_in_map(g_large_map, g_page_size * 2, NULL);
		empty_page->addr = mem;
		empty_page->size = request_size;
	}
	else
	{
		block = find_free_memory(g_tiny_map, g_page_size * 2, size);
		if (block.block == NULL)
			return (0);
		*block.size_part = size;
		mem = block.block;
	}
	return (mem);
}
