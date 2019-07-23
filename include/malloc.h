/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:08:11 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 14:45:27 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <stdlib.h>

void	free(void *ptr);
void	*malloc(size_t size);
void 	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif
