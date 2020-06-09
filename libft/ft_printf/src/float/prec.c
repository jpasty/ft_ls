/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:25:59 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*format_f3(t_format *param, int i, char *tmp)
{
	if (param->plus_space == ' ' && param->sign != 1)
		param->bdot = strjf(" ", param->bdot, 0, 1);
	if (param->sign == 1)
		param->bdot = strjf("-", param->bdot, 0, 1);
	if (param->plus_space == '+' && param->sign != 1)
		param->bdot = strjf("+", param->bdot, 0, 1);
	i = ft_strlen(param->bdot);
	tmp = ft_memset(tmp, ' ', (size_t)(param->width - i));
	if (param->minus_zero == '-')
		param->bdot = strjf(param->bdot, tmp, 1, 0);
	else
		param->bdot = strjf(tmp, param->bdot, 0, 1);
	free(tmp);
	return (param->bdot);
}

char		*format_f2(t_format *param, int i)
{
	char	*tmp;

	tmp = ft_strnew(param->width - i);
	if ('0' == param->minus_zero)
	{
		tmp = ft_memset(tmp, '0', (size_t)(param->width - i));
		param->bdot = strjf(tmp, param->bdot, 0, 1);
		if (param->plus_space == ' ' && param->sign != 1)
			param->bdot = strjf(" ", param->bdot, 0, 1);
		if (param->sign == 1)
			param->bdot = strjf("-", param->bdot, 0, 1);
		if (param->plus_space == '+' && param->sign != 1)
			param->bdot = strjf("+", param->bdot, 0, 1);
		free(tmp);
	}
	else
		param->bdot = format_f3(param, i, tmp);
	return (param->bdot);
}

char		*f_format(t_format *param)
{
	int		i;

	param->adot = f_precision(param, 1);
	if (param->precision != 0 || param->hash == '#')
		param->adot = strjf(".", param->adot, 0, 1);
	if (ft_strlen(param->bdot) == 0)
		param->adot = strjf("0", param->adot, 0, 1);
	param->bdot = strjf(param->bdot, param->adot, 1, 1);
	i = ft_strlen(param->bdot);
	if (param->sign == 1 || param->plus_space == '+' || \
		param->plus_space == ' ')
		i = i + 1;
	if (param->width > 0 && param->width > (size_t)i)
		param->bdot = format_f2(param, i);
	else
	{
		if (param->plus_space == ' ' && param->sign != 1)
			param->bdot = strjf(" ", param->bdot, 0, 1);
		if (param->sign == 1)
			param->bdot = strjf("-", param->bdot, 0, 1);
		if (param->plus_space == '+' && param->sign != 1)
			param->bdot = strjf("+", param->bdot, 0, 1);
	}
	return (param->bdot);
}

char		*g_format(t_format *param, int neg, int pos)
{
	if (param->precision == -1)
		param->precision = 5;
	else if (param->precision == 0 || param->precision == 1)
		param->precision = 1;
	else
		param->precision = param->precision - 1;
	if (pos >= param->precision || (neg + 1) > 4)
		param->bdot = e_format(param);
	else
		param->bdot = g_precision(param);
	return (param->bdot);
}

char		*check_format(t_format *param)
{
	size_t	pos;
	int		neg;
	char	*res;

	pos = ft_strlen(param->bdot) - 1;
	neg = 0;
	if (param->adot[neg] == '0')
	{
		while (param->adot[neg] == '0')
			neg++;
	}
	if (param->float_type == 'g')
		param->bdot = g_format(param, neg, pos);
	else
	{
		if (param->precision == -1)
			param->precision = 6;
		if (param->float_type == 'e')
			param->bdot = e_format(param);
		else
			param->bdot = f_format(param);
	}
	res = param->bdot;
	return (res);
}
