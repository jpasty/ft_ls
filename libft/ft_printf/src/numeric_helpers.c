/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:25:27 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(unsigned long long value, int base, int reg)
{
	static char			*abc;
	char				*s;
	int					len;
	unsigned long long	tmp;

	abc = ft_strnew(16);
	abc = ft_strcpy(abc, (reg == 0) ? "0123456789abcdef" : "0123456789ABCDEF");
	len = 1;
	tmp = value;
	while (tmp > (unsigned long long)(base - 1))
	{
		tmp = tmp / (unsigned long long)base;
		len++;
	}
	s = (value == 0) ? ft_strdup("0") : ft_strnew(--len + 1);
	while (value > 0)
	{
		s[len--] = abc[value % base];
		value = value / base;
	}
	ft_strdel(&abc);
	return (s);
}

char	*add_atributes_width(t_format *param, char *str, char *tmp)
{
	char *new;

	if (str[0] == ' ' || ((str[0] == '+' || str[0] == '-') && tmp[0] == '0'))
		new = add_atributes_precision(tmp, str);
	else if ('x' == str[1] || 'X' == str[1])
		new = split_and_assemble(param, str, tmp);
	else
		new = ft_strjoin(tmp, str);
	return (new);
}

char	*split_and_assemble(t_format *param, char *str, char *tmp)
{
	char *new;

	if ((('x' == param->type || 'X' == param->type) && tmp[0] == '0'
		&& ft_strlen(tmp) >= 1) || 'p' == param->type)
	{
		str[1] = '0';
		if (ft_strlen(tmp) == 1 && param->type != 'p')
			str[0] = param->type;
	}
	new = ft_strjoin(tmp, str);
	if ((('x' == param->type || 'X' == param->type) && ft_strlen(tmp) > 1
			&& tmp[0] == '0') || 'p' == param->type)
		new[1] = ('x' == param->type || 'p' == param->type) ? 'x' : 'X';
	return (new);
}

char	*add_atributes_precision(char *tmp, char *str)
{
	char *new;
	char c;

	c = *str;
	if ((c == '-' || c == '+' || c == ' ') && tmp)
	{
		str[0] = tmp[0];
		tmp[0] = c;
	}
	new = ft_strjoin(tmp, str);
	return (new);
}
