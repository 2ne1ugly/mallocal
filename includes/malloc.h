/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:15:28 by mchi              #+#    #+#             */
/*   Updated: 2019/04/15 20:52:31 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <libft.h>
# include "util.h"

# define m	300
# define n	100

extern t_large_page	*g_large_map;
extern size_t		*g_small_map;
extern size_t		*g_tiny_map;
extern size_t		g_page_size;

void			*malloc(size_t size);
void			free(void *ptr);
void 			show_alloc_mem();

#endif
