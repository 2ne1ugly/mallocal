/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:11:37 by mchi              #+#    #+#             */
/*   Updated: 2019/04/21 15:32:41 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//first pointer of the page is the pointer to the next page.

void	*malloc(size_t size)
{
	size_t			*mem;
	t_large_page	*page;
	size_t			*large;

	if (!check_minor())
		return (NULL);
	if (size > m)
	{
		large = find_addr_space();
		page =
			(t_large_page *)new_map(large, lowest_multiple(g_page_size, size));
		*large = (size_t)page;
		page->page_size = lowest_multiple(g_page_size, size);
		page->size = size;
		return (&page->addr);
	}
	else
	{
		if (size > n)
			mem = find_free_block(g_small_map, size);
		else
			mem = find_free_block(g_tiny_map, size);
		if (mem == NULL)
			return (NULL);
		mem = alloc_free_block(mem, size);
	}
	return (mem);
}
