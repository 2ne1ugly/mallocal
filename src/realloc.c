/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:15:32 by mchi              #+#    #+#             */
/*   Updated: 2019/04/15 18:15:32 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*new_malloc(size_t prev_size, void *ptr, size_t size)
{
	size_t	*new_block;

	new_block = malloc(size);
	if (new_block == NULL)
		return (NULL);
	if (prev_size < size)
		ft_memcpy(new_block, ptr, prev_size);
	else
		ft_memcpy(new_block, ptr, size);	
	free(ptr);
	return (new_block);
}

void	shrink_size(size_t *block, size_t size)
{
	size_t	next_header;
	size_t	left_over;

	left_over = lowest_multiple(sizeof(size_t), block[0])
		- lowest_multiple(size);
	block[0] = size + 3 * sizeof(size_t);
	next_header = lowest_multiple(sizeof(size_t), *block) / sizeof(size_t);
	block[next_header - 1] = *block;
	block[next_header - 2] = 1;
	if (left_over > 0)
	{
		block[next_header] = left_over;
		block[next_header + left_over / sizeof(size_t) - 1] = left_over;
		block[next_header + left_over / sizeof(size_t) - 2] = 0;
		defrag_free_block(&block[next_header]);
	}
}

void	expand_size(size_t *block, size_t size)
{
	size_t	next_header;
	size_t	left_over;

	next_header = lowest_multiple(sizeof(size_t), *block) / sizeof(size_t);
	left_over =
		lowest_multiple(sizeof(size_t), block[0]) + block[next_header] -
		lowest_multiple(sizeof(size_t), size);
	block[0] = size + 3 * sizeof(size_t);
	next_header = lowest_multiple(sizeof(size_t), *block) / sizeof(size_t);
	block[next_header - 1] = *block;
	block[next_header - 2] = 1;
	if (left_over > 0)
	{
		block[next_header] = left_over;
		block[next_header + left_over / sizeof(size_t) - 1] = left_over;
		block[next_header + left_over / sizeof(size_t) - 2] = 0;
	}
}


int		has_space(size_t *block, size_t size)
{
	size_t	next_header;

	next_header = lowest_multiple(sizeof(size_t), *block) / sizeof(size_t);
	if (!is_free_header(block[next_header]))
		return (0);
	if (block[0] + block[next_header] - 3 * sizeof(size_t) < size)
		return (0);
	return (1);
}

void	*realloc(void *ptr, size_t size)
{
	size_t	*block;

	block = ptr;
	block = block[-1];
	if (block[0] - 3 * sizeof(size_t) == size)
		return (ptr);
	if (block[0] - 3 * sizeof(size_t) > m ||
		(block[0] - 3 * sizeof(size_t) > n && size <= n) ||
		(block[0] - 3 * sizeof(size_t) <= n && size > n))
		return (new_malloc(block[0] - 3, ptr, size));
	if (block[0] - 3 * sizeof(size_t) > size)
	{
		shrink_size(block, size);
	}
	else if (has_space(block, size))
	{
		expand_size(block, size)
	}
	else
		return (new_malloc(block[0] - 3, ptr, size));
}
