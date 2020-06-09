/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:08:50 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		clean_mult(t_mult *mult)
{
	free(mult->zero);
	free(mult->s1);
	free(mult->s2);
	free(mult);
}

void		clean_sum(t_sum *sum)
{
	free(sum->carryc);
	free(sum);
}

void		clr_float_params(t_format *param)
{
	param->bdot = ft_strdup("");
	param->adot = ft_strdup("");
	param->zero = "0";
	param->ten = "10";
	param->one = "1";
}

char		*ft_strsubf(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	sub = ft_strnew(len);
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	free(s);
	return (sub);
}

char		*pointer_precision(t_format *param, char *str, size_t len)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	tmp = ft_strnew(param->precision - len + 2);
	while (param->precision - (int)len + 2 > i)
		tmp[i++] = '0';
	new = (param->width <= (ft_strlen(tmp) + len))
		? split_and_assemble(param, str, tmp) : ft_strjoin(tmp, str);
	ft_strdel(&tmp);
	ft_strdel(&str);
	return (new);
}
