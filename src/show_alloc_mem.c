/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:38:09 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 16:24:08 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_hex(size_t val)
{
	const char charset[] = "0123456789ABCDEF";

	if (val >= 16)
		print_hex(val / 16);
	ft_putchar(charset[val % 16]);
}

