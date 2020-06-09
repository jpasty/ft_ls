/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:46:42 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*res;
	const unsigned char *str;
	size_t				i;

	i = 0;
	res = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (src < dst)
	{
		while (len--)
			res[len] = str[len];
	}
	else
	{
		while (len--)
		{
			res[i] = str[i];
			i++;
		}
	}
	return (res);
}
