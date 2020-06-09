/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:24:17 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *dst, const char *src, size_t len)
{
	char		*s1;
	char		*s2;
	size_t		nl;

	s1 = (char *)dst;
	s2 = (char *)src;
	nl = ft_strlen(s2);
	if (*s2 == '\0')
		return (s1);
	while (*s1 && len-- >= nl)
	{
		if (*s1 == *s2 && (ft_memcmp(s1, s2, nl) == 0))
			return (s1);
		s1++;
	}
	return (NULL);
}
