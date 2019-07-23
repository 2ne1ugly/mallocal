/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:07:38 by mchi              #+#    #+#             */
/*   Updated: 2019/07/22 23:27:22 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_STRUCT_H
# define MALLOC_STRUCT_H

#include "malloc_int.h"

# define ST sizeof(size_t)
# define T_BUFF_CAP 512
# define S_BUFF_CAP	2048
# define T_MAP_SIZE (128 * T_BUFF_CAP)
# define S_MAP_SIZE (128 * S_BUFF_CAP)
# define T_BLOCK_SIZE (T_MAP_SIZE - 4 * ST)
# define S_BLOCK_SIZE (S_MAP_SIZE - 4 * ST)
# define MAP_MAP_SIZE 4096

typedef struct	s_meta
{
	size_t	cap;
	size_t	req;
}				t_meta;

/*
**	get rid of "back" maybe shrink the start mark.
*/

typedef struct	s_tiny
{
	struct s_tiny	**back;
	t_meta			start_mark;
	size_t			block[T_BLOCK_SIZE / ST];
	size_t			end_mark;
}				t_tiny;

typedef struct	s_small
{
	struct s_small	**back;
	t_meta			start_mark;
	size_t			block[S_BLOCK_SIZE / ST];
	size_t			end_mark;
}				t_small;

/*
**	large has end mark.
*/

typedef struct	s_large
{
	struct s_large	**back;
	t_meta			start_mark;
	t_meta			header;
	void			*data;
}				t_large;

typedef struct	s_map_map
{
	size_t				count;
	size_t				start_mark;
	void				*block[MAP_MAP_SIZE / ST - 4];
	size_t				next_mark;
	struct s_map_map	*next;
}				t_map_map;

#endif
