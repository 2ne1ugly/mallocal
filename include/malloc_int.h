/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:09:26 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 15:33:13 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_INT_H
# define MALLOC_INT_H

# include "malloc.h"
# include <libft.h>
# include <sys/mman.h>
# include <unistd.h>

# include "malloc_struct.h"

struct
{
	t_map_map	tiny;
	t_map_map	small;
	t_map_map	large;
	t_tiny		tiny_prealloc;
	t_small		small_prealloc;
	int			set;
}				g_mal;

void			*find_tiny_free(t_tiny *m, size_t size);
void			*find_small_free(t_small *m, size_t size);

void			*aquire_buffer(t_meta *header, size_t size, size_t req);
int				is_capable(t_meta *meta, size_t size);
size_t			align(size_t n, size_t m);
void			*new_empty_map(size_t size);
void			*new_map(size_t size);

void			init_g_mal();
void			*tiny_malloc(t_map_map *m, size_t size);
void			*small_malloc(t_map_map *m, size_t size);
void			*large_malloc(t_map_map *m, size_t size);

int				validate_meta(t_meta *meta);
void			unmap_large(t_meta *meta);
void			delete_map_elem(void **elem);

void			defrag_meta(t_meta *meta);
void			free_buffer(t_meta *header);

#endif
