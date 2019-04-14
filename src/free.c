/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 22:29:34 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 16:30:15 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void	free(void *ptr)
{
	t_page		*page;
	t_block		block;

	if (ptr == NULL)
		return ;
	block = find_addr_in_map(g_tiny_map, g_page_size * 2, ptr);
	if (block.block == NULL)
		block = find_addr_in_map(g_small_map, g_page_size * 2, ptr);
	if (block.block == NULL)
	{
		page = find_elem_in_map(g_large_map, g_page_size * 2, ptr);
		if (page == NULL)
		{
			printf("MAJOR ERROR!!!!!\n");
			exit(1);
		}
		munmap(ptr, page->size);
		page->addr = 0;
		page->size = 0;
		return ;
	}
	ft_bzero(block.block, *block.size_part);
	*block.size_part = 0;
}
