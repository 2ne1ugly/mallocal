/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_per.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:36:54 by mchi              #+#    #+#             */
/*   Updated: 2019/05/25 19:37:14 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

t_vec	fmt_per(t_opt *opt, va_list *arg)
{
	t_vec	out;

	(void)arg;
	init_vec(&out);
	push_back_str(&out, "%", 1);
	pad_width(&out, opt);
	return (out);
}
