/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 15:21:19 by user              #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strcspn(const char *str, const char *sym)
{
	const char	*s;
	const char	*c;

	s = str;
	while (*str)
	{
		c = sym;
		while (*c)
		{
			if (*str == *c)
				break ;
			c++;
		}
		if (*c)
			break ;
		str++;
	}
	return (str - s);
}
