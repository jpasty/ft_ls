/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:35:21 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t				print_unsigned(t_format *param, va_list ap)
{
	unsigned long long	arg;
	char				*tmp;
	char				*str;
	size_t				len;

	arg = get_unsigned(param, ap);
	tmp = (!arg && !param->precision) ? ft_strdup("")
		: ft_itoa_base(arg, 10, 0);
	str = fill_zero_unsigned(param, tmp, ft_strlen(tmp));
	str = print_width(param, str, ft_strlen(str));
	len = write(1, str, ft_strlen(str));
	ft_strdel(&str);
	return (len);
}

char				*fill_zero_unsigned(t_format *param, char *str, size_t len)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	if (param->precision > (int)len)
	{
		tmp = ft_strnew(param->precision - len + 1);
		while (i < param->precision - (int)len)
			tmp[i++] = '0';
		new = ft_strjoin(tmp, str);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (new);
	}
	return (str);
}

unsigned long long	get_unsigned(t_format *param, va_list ap)
{
	if (param->size == 4)
		return (va_arg(ap, unsigned long long));
	else if (param->size == 3)
		return ((unsigned long)va_arg(ap, unsigned long long));
	else if (param->size == 2)
		return ((unsigned short)va_arg(ap, unsigned long long));
	else if (param->size == 1)
		return ((unsigned char)va_arg(ap, unsigned long long));
	else
		return (va_arg(ap, unsigned int));
}
