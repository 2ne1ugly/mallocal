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

typedef struct	s_page
{
	size_t	size;
	void	*addr;
}				t_page;

typedef struct	s_block
{
	size_t	*size_part;
	void	**block;
	t_page	parent;
}				t_block;


#endif
