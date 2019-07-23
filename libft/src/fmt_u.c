/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:21:30 by mchi              #+#    #+#             */
/*   Updated: 2019/05/25 20:22:48 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

void	u_set_arg(uintmax_t *val, int length, va_list *arg)
{
	if (length == 0 || length == 1 || length == 2)
		*val = va_arg(*arg, unsigned int);
	else if (length == 3)
		*val = va_arg(*arg, unsigned long int);
	else if (length == 4)
		*val = va_arg(*arg, unsigned long long int);
	else if (length == 5)
		*val = va_arg(*arg, uintmax_t);
	else if (length == 6)
		*val = va_arg(*arg, size_t);
	else if (length == 7)
		*val = va_arg(*arg, ptrdiff_t);
}

void	add_o_pre_prefix(t_vec *vec, t_opt *opt, int *o_pre)
{
	*o_pre = 0;
	if (*vec->ptr != '0')
	{
		*o_pre = 1;
		if (opt->flags & ZERO)
			opt->width--;
		else
			push_front_str(vec, "0", 1);
	}
}

void	add_o_post_prefix(t_vec *vec, t_opt *opt, int *o_pre)
{
	if (*o_pre && opt->flags & ZERO)
		push_front_str(vec, "0", 1);
}

void	u_handle_base(t_vec *out, t_opt *opt, uintmax_t val)
{
	int o_pre;

	if (opt->spec == 'u')
		max_itoa_base(out, val, 10, FALSE);
	else if (opt->spec == 'o')
		max_itoa_base(out, val, 8, FALSE);
	else if (opt->spec == 'x' || opt->spec == 'X')
		max_itoa_base(out, val, 16, opt->spec == 'X');
	pad_num_precision(out, opt);
	if ((opt->flags & SHARP) && opt->spec == 'o')
		add_o_pre_prefix(out, opt, &o_pre);
	else if ((opt->flags & SHARP) && opt->spec == 'x' && val != 0)
		add_pre_prefix(out, opt, "0x");
	else if ((opt->flags & SHARP) && opt->spec == 'X' && val != 0)
		add_pre_prefix(out, opt, "0X");
	pad_width(out, opt);
	if ((opt->flags & SHARP) && opt->spec == 'o')
		add_o_post_prefix(out, opt, &o_pre);
	else if ((opt->flags & SHARP) && opt->spec == 'x' && val != 0)
		add_post_prefix(out, opt, "0x");
	else if ((opt->flags & SHARP) && opt->spec == 'X' && val != 0)
		add_post_prefix(out, opt, "0X");
}

t_vec	fmt_u(t_opt *opt, va_list *arg)
{
	uintmax_t	val;
	t_vec		out;

	if (opt->precision == -1)
		opt->precision = 1;
	else
		opt->flags &= ~ZERO;
	u_set_arg(&val, opt->length, arg);
	init_vec(&out);
	u_handle_base(&out, opt, val);
	return (out);
}
