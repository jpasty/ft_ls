/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbolic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:55:26 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		print_percent(t_format *param)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	if (param->width > 1)
	{
		tmp = ft_strnew(param->width - 1);
		while (i < (int)(param->width - 1))
			tmp[i++] = (param->minus_zero != '0') ? ' ' : '0';
		new = (param->minus_zero == '-')
			? ft_strjoin("%", tmp) : ft_strjoin(tmp, "%");
		ft_strdel(&tmp);
		i = write(1, new, ft_strlen(new));
		ft_strdel(&new);
		return (i);
	}
	return (write(1, "%", 1));
}

size_t		print_chr(t_format *param, va_list ap)
{
	char	arg;
	size_t	len;
	size_t	count;

	arg = ('c' == param->type) ? (char)va_arg(ap, int) : param->type;
	if (param->width > 1)
	{
		count = ('-' == param->minus_zero) ? write(1, &arg, 1) : 0;
		len = param->width - 1;
		while (len > 0)
		{
			count += write(1, (param->minus_zero != '0') ? " " : "0", 1);
			len--;
		}
		if (param->minus_zero != '-')
			count += write(1, &arg, 1);
	}
	else
		count = write(1, &arg, 1);
	return (count);
}

size_t		print_str(t_format *param, va_list ap)
{
	char	*arg;
	char	*new;
	size_t	len;

	arg = va_arg(ap, char *);
	arg = ft_strdup((!arg) ? "(null)" : arg);
	if (param->precision != -1 && param->precision < (int)ft_strlen(arg))
	{
		len = 0;
		new = ft_strnew(param->precision);
		while (param->precision > (int)len)
		{
			new[len] = arg[len];
			len++;
		}
		ft_strdel(&arg);
		arg = ft_strdup(new);
		ft_strdel(&new);
	}
	len = ft_strlen(arg);
	if (param->width > len)
		arg = string_width(param, arg, len);
	len = write(1, arg, ft_strlen(arg));
	free(arg);
	return (len);
}

char		*string_width(t_format *param, char *str, size_t len)
{
	char	*tmp;
	char	*new;
	size_t	i;

	i = 0;
	tmp = ft_strnew(param->width - len);
	while ((int)param->width - len > i)
		tmp[i++] = (param->minus_zero != '0') ? ' ' : '0';
	new = (param->minus_zero == '-')
		? ft_strjoin(str, tmp) : ft_strjoin(tmp, str);
	ft_strdel(&tmp);
	ft_strdel(&str);
	return (new);
}

size_t		print_pointer(t_format *param, va_list ap)
{
	unsigned long long int	arg;
	char					*tmp;
	char					*str;
	size_t					len;

	arg = (unsigned long long int)va_arg(ap, void *);
	if (!param->precision && !arg)
		str = ft_strdup("0x");
	else
	{
		tmp = ft_itoa_base(arg, 16, 0);
		str = ft_strjoin("0x", tmp);
		ft_strdel(&tmp);
	}
	if (param->precision > (int)(len = ft_strlen(str)))
		str = pointer_precision(param, str, len);
	str = print_width(param, str, ft_strlen(str));
	len = write(1, str, ft_strlen(str));
	free(str);
	return (len);
}
