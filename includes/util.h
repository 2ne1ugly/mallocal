/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 22:17:17 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 17:11:43 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdio.h>
# include "page.h"
# define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
# define ALIGNMENT 8
# define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

extern t_page	*g_large_map;
extern t_page	*g_small_map;
extern t_page	*g_tiny_map;
extern size_t	g_page_size;

int		lowest_multiple(int mult, int val);
int		check_minor(void);

t_page	*find_elem_in_map(t_page *map, size_t map_size, void *ptr);
t_block	find_block_in_page(char *page, size_t map_size, void *ptr);
t_block	find_addr_in_map(t_page *map, size_t map_size, void *ptr);
t_block	find_free_memory_in_page(char *page, size_t map_size, size_t request);
t_block find_free_memory(t_page *map, size_t map_size, size_t request);

void	*new_map(size_t request);

#endif
