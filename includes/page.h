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
	void	*page_loc;
	size_t	page_size;
	size_t	size;
	size_t	addr;
}				t_large_page;

/*
**	small, tiny: 
*/

/*
**	the malloc flag takes the whole size_t just before the footer
*/

/*
**	first two memory contains two value.
**	prev page and then ~2L.
*/

/*
**	last two memory contains two value.
**	~4L and then page to next.
*/

#endif
