/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:17:54 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	5 - L
**	4 - ll
**	3 - l
**	2 - h
**	1 - hh
*/

size_t	print_int(t_format *param, va_list ap)
{
	long long int	arg;
	char			*tmp;
	char			*str;
	ssize_t			sign;

	if (param->size == 4)
		arg = va_arg(ap, long long int);
	else if (param->size == 3)
		arg = (long int)va_arg(ap, long int);
	else if (param->size == 2)
		arg = (short)va_arg(ap, long long int);
	else if (param->size == 1)
		arg = (signed char)va_arg(ap, long long int);
	else
		arg = (int)va_arg(ap, long long int);
	sign = (arg < 0) ? -1 : 1;
	tmp = (param->precision == 0 && arg == 0)
		? ft_strdup("") : ft_itoa_base(arg * sign, 10, 0);
	str = print_int2(param, tmp, sign);
	sign = write(1, str, ft_strlen(str));
	ft_strdel(&str);
	return (sign);
}

char	*print_int2(t_format *param, char *str, int sign)
{
	char	*new;

	if (sign == -1)
	{
		new = str;
		str = ft_strjoin("-", str);
		free(new);
	}
	if (param->precision >= (int)ft_strlen(str))
		str = fill_zero(param, str, ft_strlen(str));
	if (!ft_strchr(str, '-') && param->plus_space)
	{
		new = str;
		str = ('+' == param->plus_space)
			? ft_strjoin("+", new) : ft_strjoin(" ", new);
		free(new);
	}
	str = print_width(param, str, ft_strlen(str));
	return (str);
}

char	*fill_zero(t_format *param, char *str, size_t len)
{
	int		diff;
	char	*tmp;
	char	*new;

	diff = (str[0] == '-')
		? param->precision - (int)len + 1 : param->precision - (int)len;
	tmp = ft_strnew(diff);
	while (diff > 0)
		tmp[diff-- - 1] = '0';
	new = ((param->type == 'x' || param->type == 'X') &&
		(str[1] == 'x' || str[1] == 'X'))
		? split_and_assemble(param, str, tmp)
		: add_atributes_precision(tmp, str);
	ft_strdel(&str);
	ft_strdel(&tmp);
	return (new);
}

char	*print_width(t_format *param, char *str, size_t len)
{
	char *tmp;
	char *new;

	if (param->width > len)
	{
		len = param->width - len;
		tmp = ft_strnew(len);
		tmp = ft_memset(tmp, ((param->minus_zero == '0' &&
			param->precision == -1) ? '0' : ' '), len);
		if ('0' == param->minus_zero && param->type != 'u')
			new = add_atributes_width(param, str, tmp);
		else if ('0' == param->minus_zero && 'p' == param->type)
			new = split_and_assemble(param, str, tmp);
		else if ('-' == param->minus_zero)
			new = ft_strjoin(str, tmp);
		else
			new = ft_strjoin(tmp, str);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (new);
	}
	return (str);
}
