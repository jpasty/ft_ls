/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:23:13 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islocate(char *s1, char *s2)
{
	while (*s2)
	{
		if (*s1++ != *s2++)
			return (0);
	}
	return (1);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	char	*s1;
	char	*s2;

	s1 = (char *)haystack;
	s2 = (char *)needle;
	if (*s2 == '\0')
		return (s1);
	while (*s1)
	{
		if (*s1 == *s2 && ft_islocate(s1, s2))
			return (s1);
		s1++;
	}
	return (NULL);
}
