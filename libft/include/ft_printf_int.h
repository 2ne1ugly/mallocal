/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:18:12 by mchi              #+#    #+#             */
/*   Updated: 2019/05/27 12:24:05 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INT_H
# define FT_PRINTF_INT_H
# include "ft_printf.h"
# include <stdarg.h>
# include <stdlib.h>
# include <libft.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>

# define FALSE 0
# define TRUE 1

# define MINUS 1
# define PLUS 2
# define SPACE 4
# define SHARP 8
# define ZERO 16

# define HH 1
# define H 2
# define LL 3
# define SL 4
# define J 5
# define Z 6
# define T 7
# define L 8

typedef struct	s_opt
{
	int		flags;
	int		width;
	int		precision;
	int		length;
	char	spec;
}				t_opt;

typedef struct	s_vec
{
	int		size;
	int		cap;
	char	*ptr;
}				t_vec;

void			init_vec(t_vec *vec);
void			push_back_str(t_vec *vec, const char *str, int n);
void			push_front_str(t_vec *vec, const char *str, int n);
void			free_vec(t_vec *vec);
void			expand_vec(t_vec *vec, int n);
void			null_ter_vec(t_vec *vec);
t_opt			parse_opt(const char **str, va_list *arg);

t_vec			fmt_c(t_opt *opt, va_list *arg);
t_vec			fmt_s(t_opt *opt, va_list *arg);
t_vec			fmt_p(t_opt *opt, va_list *arg);
void			fmt_n(t_opt *opt, va_list *arg, int size);
t_vec			fmt_d(t_opt *opt, va_list *arg);
t_vec			fmt_u(t_opt *opt, va_list *arg);
t_vec			fmt_f(t_opt *opt, va_list *arg);
t_vec			fmt_b(t_opt *opt, va_list *arg);
t_vec			fmt_per(t_opt *opt, va_list *arg);

void			add_pre_sign(t_vec *vec, t_opt *opt, int is_neg);
void			add_post_sign(t_vec *vec, t_opt *opt, int is_neg);
void			pad_width(t_vec *vec, t_opt *opt);
void			pad_num_precision(t_vec *vec, t_opt *opt);
void			max_itoa_base(t_vec *v, uintmax_t val, int base, int i);
void			add_pre_prefix(t_vec *vec, t_opt *opt, char *str);
void			add_post_prefix(t_vec *vec, t_opt *opt, char *str);

long double		ft_log10(long double y);
long double		ft_pow(long double x, int y);
void			format_this(t_vec *vec, const char **format, va_list *list);
#endif
