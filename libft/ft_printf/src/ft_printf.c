/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:36:11 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;

	if (!format)
		return (-1);
	va_start(ap, format);
	if (format[0] == '%' && format[1] == '\0')
		return (0);
	i = format_manager(format, ap);
	va_end(ap);
	return (i);
}

size_t			format_manager(const char *format, va_list ap)
{
	size_t		length;
	t_format	*param;

	length = 0;
	param = format_initialize();
	while (format[param->i])
	{
		if (format[param->i] == '{' && format[param->i + 1 != '%'])
			param->i += colorize(&format[param->i + 1]);
		if (format[param->i] == '%')
		{
			param->i++;
			format_parser(format, param, ap);
			length += print_argument(param, param->type, ap);
			format_clean(param);
			if (format[param->i++] == '\0')
				break ;
		}
		else
			length += write(1, &format[param->i++], 1);
	}
	free(param);
	return (length);
}

t_format		*format_initialize(void)
{
	t_format	*param;

	if (!(param = (t_format*)malloc(sizeof(t_format))))
		return (NULL);
	param->hash = '\0';
	param->minus_zero = '\0';
	param->plus_space = '\0';
	param->float_type = '\0';
	param->type = '\0';
	param->precision = -1;
	param->i = 0;
	param->size = 0;
	param->sign = 0;
	param->width = 0;
	param->adot = "";
	param->bdot = "";
	param->zero = "0";
	param->ten = "10";
	param->one = "1";
	return (param);
}

void			format_clean(t_format *param)
{
	param->hash = '\0';
	param->minus_zero = '\0';
	param->plus_space = '\0';
	param->precision = -1;
	param->width = 0;
	param->size = 0;
	param->type = '\0';
	param->float_type = '\0';
	param->sign = 0;
}
