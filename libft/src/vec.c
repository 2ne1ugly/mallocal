/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:48:09 by mchi              #+#    #+#             */
/*   Updated: 2019/05/25 23:46:36 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

void	init_vec(t_vec *vec)
{
	vec->size = 0;
	vec->ptr = malloc(sizeof(char) * 16);
	vec->cap = 16;
}

void	expand_vec(t_vec *vec, int n)
{
	int		desired;
	char	*new_arr;

	desired = vec->cap;
	while (n > desired)
		desired *= 2;
	new_arr = malloc(desired);
	ft_memcpy(new_arr, vec->ptr, vec->size);
	free(vec->ptr);
	vec->ptr = new_arr;
}

void	push_back_str(t_vec *vec, const char *str, int n)
{
	if (vec->size + n + 1 >= vec->cap)
		expand_vec(vec, vec->size + n + 1);
	ft_memcpy(&vec->ptr[vec->size], str, n);
	vec->size += n;
}

void	push_front_str(t_vec *vec, const char *str, int n)
{
	if (vec->size + n + 1 >= vec->cap)
		expand_vec(vec, vec->size + n + 1);
	ft_memmove(&vec->ptr[n], vec->ptr, vec->size);
	ft_memcpy(vec->ptr, str, n);
	vec->size += n;
}

void	free_vec(t_vec *vec)
{
	free(vec->ptr);
}
