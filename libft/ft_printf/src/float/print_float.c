/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:54:59 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format			*ftoa_exp(int exp_of_two, char *res, t_format *param)
{
	int				i;

	i = 0;
	while (ft_abs(exp_of_two) > i++)
		res = ft_add(res, res, 0, 1);
	if (exp_of_two < 0)
	{
		res = ft_negs(res);
		param->adot = ft_add(res, param->adot, 1, 2);
	}
	else
		param->bdot = ft_add(res, param->bdot, 0, 2);
	return (param);
}

char				*ft_ftoa(char *mnt, int e, t_format *param)
{
	char			*res;
	int				i;
	int				shift;
	int				val;
	int				exp_of_two;

	i = 63;
	shift = 0;
	while (i >= 0)
	{
		val = mnt[i];
		if (val == 1)
		{
			res = ft_strdup("1");
			exp_of_two = e - shift;
			param = ftoa_exp(exp_of_two, res, param);
		}
		shift++;
		i--;
	}
	res = check_format(param);
	free(mnt);
	return (res);
}

char				*put_bits(unsigned char *mnt)
{
	char			*res_mnt;
	int				i;
	int				n;
	int				bit_mask;

	res_mnt = ft_strnew(64);
	i = 0;
	n = 0;
	while (n < 8)
	{
		bit_mask = 1;
		while (bit_mask != 256)
		{
			res_mnt[i] = (mnt[n] & bit_mask) ? 1 : 0;
			bit_mask <<= 1;
			i++;
		}
		n++;
	}
	return (res_mnt);
}

char				*get_value(t_format *param, int e, unsigned long m)
{
	char			*str_mant;
	char			*out;

	if (e == 16384)
		out = exceptions(m, param->sign);
	else
	{
		str_mant = put_bits((unsigned char *)&m);
		out = ft_ftoa(str_mant, e, param);
	}
	return (out);
}

size_t				print_float(t_format *param, va_list ap)
{
	int				e;
	unsigned long	m;
	char			*res;

	if (param->bdot && param->adot)
		clr_float_params(param);
	if (ap == NULL)
		return (0);
	if (param->size == 5)
		fl.num = va_arg(ap, long double);
	else
		fl.num = (long double)va_arg(ap, double);
	param->sign = fl.val.sign;
	if (fl.val.exp != 1)
	{
		e = fl.val.exp - 16383;
		m = fl.val.mant;
	}
	else
	{
		e = 1;
		m = 0;
	}
	res = get_value(param, e, m);
	return (str_to_out(res));
}
