/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:00:18 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_abs(int nb)
{
	return (nb > 0 ? nb : -nb);
}

size_t		ft_max(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	return (l1 > l2 ? l1 : l2);
}

size_t		ft_min(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	return (l1 < l2 ? l1 : l2);
}

int			ft_chararcmp(char *a, char *b)
{
	int		i;

	i = 0;
	if (ft_strlen(a) > ft_strlen(b))
		return (1);
	if (ft_strlen(a) < ft_strlen(b))
		return (-1);
	else
	{
		while (a[i] != '\0')
		{
			if (ft_strcmp(&a[i], &b[i]) > 0)
				return (1);
			if (ft_strcmp(&a[i], &b[i]) < 0)
				return (-1);
			else
				i++;
		}
	}
	return (0);
}
