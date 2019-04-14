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

void	print_all_block(char *page, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (*(size_t *)&page[i] == 0)
			i++;
		else
		{
			print_hex(page[i] + sizeof(size_t));
			i += *(size_t *)&page[i] + sizeof(size_t);
		}
	}
}

void	print_small_mid(t_page	*page, char *name)
{
	size_t	max_element;
	size_t	i;

	max_element = g_page_size * 2 / sizeof(t_page);
	ft_putstr(name);
	ft_putstr(" : ");
	ft_putstr("0x");
	print_hex((size_t)g_large_map);
	ft_putchar('\n'); 
	i = 0;
	while (i < max_element - 1 || page[i].addr != NULL)
	{
		if (i == max_element - 1)
		{
			page = page[i].addr;
			i = 0;
		}
		if (page[i].addr != 0)
		{
			print_all_block(page[i].addr, page[i].size);
		}
		i++;
	}
}

void	print_large(void)
{
	size_t	max_element;
	size_t	i;
	t_page	*curr_page;

	i = 0;
	max_element = g_page_size * 2 / sizeof(t_page);
	ft_putstr("LARGE : ");
	ft_putstr("0x");
	print_hex((size_t)g_large_map);
	ft_putchar('\n');
	curr_page = g_large_map;
	while (i < max_element - 1 || curr_page[i].addr != NULL)
	{
		if (i == max_element - 1)
		{
			curr_page = curr_page[i].addr;
			i = 0;
		}
		if (curr_page[i].addr != 0)
		{
			ft_putstr("0x");
			print_hex((size_t)curr_page[i].addr);
			ft_putstr(" - ");
			ft_putstr("0x");
			print_hex((size_t)(curr_page[i].addr + curr_page[i].size));
			ft_putstr(" : ");
			ft_putnbr(curr_page[i].size);
			ft_putstr("bytes\n");
		}
		i++;
	}
}

void 	show_alloc_mem(void)
{
	print_small_mid(g_tiny_map, "TINY");
	print_small_mid(g_small_map, "SMALL");
	print_large();
}
