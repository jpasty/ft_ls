/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21.school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:16:19 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		print_oct(t_format *param, va_list ap)
{
	unsigned long long	arg;
	char				*tmp;
	char				*str;
	size_t				len;

	arg = get_unsigned(param, ap);
	tmp = ft_itoa_base(arg, 8, 0);
	if (param->hash != '#' && 0 == param->precision && 0 == arg)
		str = ft_strdup("");
	else if ('#' == param->hash && tmp[0] != '0')
	{
		str = ft_strjoin("0", tmp);
		ft_strdel(&tmp);
	}
	else
		str = tmp;
	len = ft_strlen(str);
	if (param->precision >= (int)len)
		str = fill_zero(param, str, len);
	str = print_width(param, str, ft_strlen(str));
	len = write(1, str, ft_strlen(str));
	ft_strdel(&str);
	return (len);
}

size_t		print_hex(t_format *param, va_list ap)
{
	unsigned long long	arg;
	char				*tmp;
	char				*str;
	size_t				len;

	arg = get_unsigned(param, ap);
	tmp = ft_itoa_base(arg, 16, (param->type == 'X') ? 1 : 0);
	if (!param->precision && !arg)
		str = ft_strdup("");
	else if ('#' == param->hash && tmp[0] != '0')
	{
		str = ft_strjoin(('x' == param->type) ? "0x" : "0X", tmp);
		ft_strdel(&tmp);
	}
	else
		str = tmp;
	len = ft_strlen(str) - ((str[1] == 'X' || str[1] == 'x') ? 2 : 0);
	if (param->precision >= (int)len)
		str = fill_zero(param, str, len);
	str = print_width(param, str, ft_strlen(str));
	len = write(1, str, ft_strlen(str));
	ft_strdel(&str);
	return (len);
}
