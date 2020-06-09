/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:28:23 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*g_precision(t_format *param)
{
	int		neg;
	char	*tmp;

	neg = ft_strlen(param->adot);
	if (neg > param->precision)
		param->adot = cropp(param->adot, param->precision, param->one);
	if (param->adot[param->precision - 1] == '0' && param->hash != '#')
	{
		param->precision--;
		while (param->adot[param->precision] == '0')
			param->precision--;
		tmp = param->adot;
		param->adot = ft_strsub(param->adot, 0, param->precision + 1);
		free(tmp);
	}
	if ((param->precision != 0 && neg != 0) || param->hash == '#')
		param->adot = strjf(".", param->adot, 0, 1);
	if (ft_strlen(param->bdot) == 0)
		param->adot = strjf("0", param->adot, 0, 1);
	if (param->sign == 1)
		param->bdot = strjf("-", param->bdot, 0, 1);
	param->bdot = strjf(param->bdot, param->adot, 1, 1);
	return (param->bdot);
}

char		*e_prec2(t_format *param, char *new, char *one)
{
	int		neg;

	while (new[param->precision] == '0')
		param->precision--;
	new = ft_strsubf(new, 0, param->precision);
	if (param->float_type == 'g' && param->hash != '#')
	{
		while (new[param->precision - 1] == '0')
			param->precision--;
		new = ft_strsubf(new, 0, param->precision);
	}
	if (param->precision != 0)
		new = strjf(".", new, 0, 1);
	neg = ft_strlen(new);
	if (neg <= param->precision && param->precision != 0)
	{
		while (neg <= param->precision)
		{
			new = strjf(new, "0", 1, 0);
			neg++;
		}
	}
	param->bdot = strjf(one, new, 1, 1);
	return (param->bdot);
}

char		*e_prec(t_format *param, char *sign, char *e)
{
	int		len;
	int		i;
	int		len2;
	char	*new;
	char	*one;

	i = 0;
	while (param->bdot[i] == '0')
		i++;
	one = ft_strnew(1);
	one[0] = param->bdot[i];
	len = ft_strlen(param->bdot);
	len2 = 0;
	new = ft_strnew(len);
	while (len2 != len)
	{
		new[len2] = param->bdot[len2 + i + 1];
		len2++;
	}
	if (len > param->precision)
		new = cropp(new, param->precision, param->one);
	param->bdot = e_prec2(param, new, one);
	param->bdot = strjf(param->bdot, sign, 1, 0);
	param->bdot = strjf(param->bdot, e, 1, 1);
	return (param->bdot);
}

char		*e_min(t_format *param, int neg, char *e)
{
	char	*sign;
	char	*ee;

	sign = "e-";
	if (param->adot[neg] == '0')
	{
		while (param->adot[neg] == '0')
			neg++;
	}
	ee = ft_itoa(neg + 1);
	e = ft_add(e, ee, 0, 2);
	param->bdot = param->adot;
	param->bdot = e_prec(param, sign, e);
	return (param->bdot);
}

char		*e_format(t_format *param)
{
	int		pos;
	int		neg;
	char	*sign;
	char	*e;
	char	*ee;

	pos = (int)ft_strlen(param->bdot) - 1;
	neg = 0;
	e = "00";
	if (pos >= 0)
	{
		sign = "e+";
		ee = ft_itoa(pos);
		e = ft_add(e, ee, 0, 3);
		param->bdot = strjf(param->bdot, param->adot, 1, 1);
		ee = param->bdot;
		param->bdot = e_prec(param, sign, e);
		free(ee);
	}
	else
		e_min(param, neg, e);
	return (param->bdot);
}
