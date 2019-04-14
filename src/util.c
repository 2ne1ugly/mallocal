/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 22:14:18 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 15:28:02 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		lowest_multiple(int mult, int val)
{
	return (((val / mult) + 1) * mult);
}

int		check_minor(void)
{
	if (g_page_size != 0)
		return (1);
	g_page_size = getpagesize();
	if (!g_large_map && !(g_large_map = new_map(g_page_size * 2)))
		return (0);
	if (!g_small_map && !(g_small_map = new_map(g_page_size * 2)))
		return (0);
	if (!g_tiny_map && !(g_tiny_map = new_map(g_page_size * 2)))
		return (0);
	ft_bzero(g_large_map, g_page_size * 2);
	ft_bzero(g_small_map, g_page_size * 2);
	ft_bzero(g_tiny_map, g_page_size * 2);
	return (1);
}

void	*new_map(size_t request)
{
	void	*mem;

	mem = mmap(NULL, request, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (mem == MAP_FAILED)
		mem = NULL;
	return (mem);
}
