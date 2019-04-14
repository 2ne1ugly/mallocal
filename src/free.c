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
	size_t	*size;

	if (ptr == NULL)
		return ;
	size = (size_t *)(ptr - sizeof(size_t));
	if (size >= LARGE + 1)
	{
		delete_addr(size);
		munmap(size, *size);
	}
	else
		*size &= ~1L;
}
