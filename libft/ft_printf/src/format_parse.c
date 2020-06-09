/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:51:14 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	format_parser(const char *format, t_format *param, va_list ap)
{
	flags_parser(format, param);
	width_prcsn_parser(format, param, ap);
	size_parser(format, param);
	param->type = format[param->i];
}

void	flags_parser(const char *format, t_format *param)
{
	size_t i;

	i = param->i;
	while (format[i] == '#' || format[i] == '0' || format[i] == ' ' ||
			format[i] == '+' || format[i] == '-')
	{
		if (format[i] == '#')
			param->hash = '#';
		else if ((format[i] == '-' || format[i] == '0')
				&& param->minus_zero != '-')
			param->minus_zero = format[i];
		else if ((format[i] == '+' || format[i] == ' ')
				&& (param->plus_space != '+'))
			param->plus_space = format[i];
		i = ++param->i;
	}
}

void	width_prcsn_parser(const char *format, t_format *param, va_list ap)
{
	if (format[param->i] >= '0' && format[param->i] <= '9')
	{
		param->width = ft_atoi(format + param->i);
		while (format[param->i] >= '0' && format[param->i] <= '9')
			param->i++;
	}
	else if (format[param->i] == '*' && ++param->i)
		param->width = va_arg(ap, int);
	if (format[param->i] == '.' && format[++param->i] != '*')
	{
		param->precision = ft_atoi(format + param->i);
		while (format[param->i] >= '0' && format[param->i] <= '9')
			param->i++;
	}
	else if (format[param->i] == '*' && ++param->i)
		param->precision = va_arg(ap, int);
}

void	size_parser(const char *f, t_format *param)
{
	size_t h;
	size_t l;
	size_t big_l;

	big_l = 0;
	l = 0;
	h = 0;
	while (f[param->i] == 'h' || f[param->i] == 'l' || f[param->i] == 'L')
	{
		if (f[param->i] == 'h')
			h++;
		else
			(f[param->i] == 'l') ? l++ : big_l++;
		param->i++;
	}
	if (big_l)
		param->size = 5;
	else if (big_l == 2 || (l && l % 2 == 0))
		param->size = 4;
	else if (l > 0)
		param->size = 3;
	else if (h % 2 != 0 && h > 0)
		param->size = 2;
	else if (h > 0)
		param->size = 1;
}

size_t	print_argument(t_format *param, char c, va_list ap)
{
	if (c == 'd' || c == 'i')
		return (print_int(param, ap));
	else if (c == 'o')
		return (print_oct(param, ap));
	else if (c == 'u')
		return (print_unsigned(param, ap));
	else if (c == 'x' || c == 'X')
		return (print_hex(param, ap));
	else if (c == 's')
		return (print_str(param, ap));
	else if (c == 'p')
		return (print_pointer(param, ap));
	else if (c == 'f' || c == 'e' || c == 'g')
	{
		param->float_type = c;
		return (print_float(param, ap));
	}
	else if (c == '%')
		return (print_percent(param));
	else
		return (print_chr(param, ap));
}
