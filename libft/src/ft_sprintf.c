/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:13:30 by mchi              #+#    #+#             */
/*   Updated: 2019/05/27 12:17:19 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

char	*ft_sprintf(const char *format, ...)
{
	t_vec	vec;
	va_list list;

	va_start(list, format);
	init_vec(&vec);
	while (*format != '\0')
	{
		if (*format == '%')
			format_this(&vec, &format, &list);
		else
			push_back_str(&vec, format, 1);
		format++;
	}
	write(1, vec.ptr, vec.size);
	va_end(list);
	return (vec.ptr);
}
