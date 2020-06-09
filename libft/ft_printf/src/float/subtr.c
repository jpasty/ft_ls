/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:20:02 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_subt		*create_subs(void)
{
	t_subt	*subt;

	if (!(subt = (t_subt *)malloc(sizeof(t_subt))))
		return (NULL);
	subt->carry = 0;
	subt->rem = 0;
	subt->temp = 0;
	subt->s1 = "\0";
	subt->s2 = "\0";
	subt->l = 0;
	subt->s = 0;
	subt->out = ft_strnew(0);
	subt->remc = "\0";
	return (subt);
}

char		*ft_zerotrim(t_subt *subt)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	if (!subt->out)
		return (NULL);
	len = ft_strlen(subt->out);
	while (subt->out[i] == '0')
		i++;
	if (i == len)
	{
		free(subt->out);
		return (ft_strdup("0"));
	}
	new = ft_strnew((len - i));
	while (i < len)
	{
		new[j++] = subt->out[i++];
		new[j] = '\0';
	}
	free(subt->out);
	return (new);
}

char		*substr_loop(t_subt *subt, char *out)
{
	subt->rem = 0;
	subt->temp = 0;
	subt->temp -= subt->carry;
	if (subt->l != 0)
	{
		subt->temp = subt->temp + (subt->s1[subt->l - 1] - '0');
		subt->l--;
	}
	if (subt->s != 0)
	{
		subt->temp = subt->temp - (subt->s2[subt->s - 1] - '0');
		subt->s--;
	}
	if (subt->temp < 0)
	{
		subt->carry = 1;
		subt->rem = 10 + subt->temp;
		subt->temp = subt->rem;
	}
	else
		subt->carry = 0;
	subt->remc = ft_strnew(1);
	subt->remc[0] = subt->temp + '0';
	out = strjf(subt->remc, out, 1, 1);
	return (out);
}

char		*ft_subtract(char *s1, char *s2)
{
	size_t	longest;
	t_subt	*subt;
	char	*s;

	subt = create_subs();
	subt->l = ft_strlen(s1);
	subt->s = ft_strlen(s2);
	if (subt->l >= subt->s)
		longest = subt->l;
	else
	{
		free(s1);
		return (NULL);
	}
	subt->s1 = s1;
	subt->s2 = s2;
	while (longest != 0)
	{
		subt->out = substr_loop(subt, subt->out);
		longest--;
	}
	s = ft_zerotrim(subt);
	free(subt->s1);
	free(subt);
	return (s);
}
