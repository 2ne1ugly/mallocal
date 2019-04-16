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
	size_t			*block;
	t_large_page	*page;

	if (ptr == NULL)
		return ;
	if (!check_minor())
		return (NULL);
	block = ptr;
	block = &block[-1];
	if (block[0] > m)
	{
		page = &block[-2];
		*page->page_loc = 0;
		munmap(page, page->page_size);
	}
	else
	{
		free_the_block(block);
		defrag_free_block(block);
	}
}
