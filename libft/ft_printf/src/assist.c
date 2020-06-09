/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:14:51 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*strjf(char *s1, char *s2, int k1, int k2)
{
	char	*s3;
	int		l1;
	int		l2;

	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1 || !s2 || !s3)
		return (NULL);
	l1 = 0;
	while (s1[l1])
	{
		s3[l1] = s1[l1];
		l1++;
	}
	l2 = 0;
	while (s2[l2])
	{
		s3[l1] = s2[l2++];
		l1++;
	}
	s3[l1] = '\0';
	if (k1)
		free(s1);
	if (k2)
		free(s2);
	return (s3);
}

char		*exceptions(unsigned long m, int sign)
{
	char	*out;

	if (m > 0x8000000000000000)
		out = ft_strdup("nan");
	else
	{
		out = ft_strdup("inf");
		if (sign == 1)
			out = strjf("-", out, 1, 0);
	}
	return (out);
}

char		*cropp(char *adot, int prec, char *one)
{
	char	*c;

	if (adot[prec] > '4')
	{
		c = adot;
		adot = ft_strsub(adot, 0, prec);
		free(c);
		c = adot;
		adot = ft_add(adot, one, 0, 0);
		free(c);
	}
	else
	{
		c = adot;
		adot = ft_strsub(adot, 0, prec);
		free(c);
	}
	c = adot;
	return (c);
}

char		*f_precision(t_format *params, int i)
{
	int		neg;

	neg = ft_strlen(params->adot);
	if (neg < params->precision)
	{
		while (neg < params->precision)
		{
			params->adot = strjf(params->adot, "0", 1, 0);
			neg++;
		}
	}
	else if (neg > params->precision)
		params->adot = cropp(params->adot, params->precision, params->one);
	if (ft_strlen(params->adot) > (size_t)params->precision)
	{
		params->bdot = ft_add(params->bdot, params->one, 0, 0);
		while (params->adot[i] != '\0')
		{
			params->adot[i - 1] = params->adot[i];
			i++;
		}
		params->adot = ft_strsub(params->adot, 0, params->precision);
	}
	return (params->adot);
}

size_t		str_to_out(char *str)
{
	size_t b;

	b = ft_strlen(str);
	write(1, str, b);
	ft_strdel(&str);
	return (b);
}
