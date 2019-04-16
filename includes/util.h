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

extern t_page	*g_large_map;
extern t_page	*g_small_map;
extern t_page	*g_tiny_map;
extern size_t	g_page_size;

size_t	lowest_multiple(size_t mult, size_t val);
int		check_minor(void);

void	*new_map(size_t *prev_page, size_t request);

size_t	*find_free_block(size_t *map, size_t request);
void	free_the_block(size_t *block);
void	defrag_free_block(size_t *block);
size_t	*alloc_free_block(size_t *block, size_t request);

int		is_free_header(size_t *block);
int		is_free_footer(size_t *block);

#endif
