/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_vars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 00:14:17 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 15:07:21 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include "page.h"

t_small_slab	*g_small_map = NULL;
t_tiny_slab		*g_tiny_map = NULL;
size_t			*g_large_map = NULL;
size_t			g_page_size = 0;
