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

size_t	lowest_multiple(size_t mult, size_t val)
{
	if (val % mult)
		return (val);
	return (val + mult - val % mult);
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

size_t	*new_map(size_t *prev_page, size_t request)
{
	size_t	*mem;
	size_t	count;

	count = request / sizeof(size_t);
	mem = mmap(NULL, request, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (mem == MAP_FAILED)
		mem = NULL;
	mem[0] = (size_t)prev_page;
	mem[1] = ~2L;
	mem[2] = (count - 4) * sizeof(size_t);
	mem[count - 4] = 0;
	mem[count - 3] = (count - 4) * sizeof(size_t);
	mem[count - 2] = ~4L; 
	mem[count - 1] = 0;
	return (mem);
}

int		is_free_header(size_t *block)
{
	if (*block == ~4L || *block % sizeof(size_t) != 0)
		return (0);
	return (!block[*block - 2]);
}

int		is_free_footer(size_t *block)
{
	if (*block == ~2L || *block % sizeof(size_t) != 0)
		return (0);
	return (!block[-1]);
}