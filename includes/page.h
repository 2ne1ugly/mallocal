/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:53:44 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 15:44:54 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_H
# define PAGE_H

# include <stdlib.h>

/*
**	holds any data per buffer.
*/

/*
**	last element of large map holds the address to the next page.
**	large map only contains addresses. size is stored inside.
*/

typedef struct	s_large_page
{
	size_t	size;
	char	pointer_addr;
}				t_large_page;

/*
**	holds 256 bytes multiple per buffer
*/

/*
**	first slab holds the address to the prev page.
**	it contains "~2" as a size.
*/

/*
**	last slab holds the address to the next page.
**	it contains "~4" as a size.
*/

typedef	struct	s_small_slab
{
	size_t	size;
	size_t	data[63];
}				t_small_slab;

/*
**	holds 16 bytes multiple per buffer
*/

typedef	struct	s_tiny_slab
{
	size_t	size;
	size_t	data[3];
}				t_tiny_slab;

#endif
