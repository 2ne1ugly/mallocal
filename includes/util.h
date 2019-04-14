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

int		lowest_multiple(int mult, int val);
int		check_minor(void);

void	*new_map(size_t request);

#endif
