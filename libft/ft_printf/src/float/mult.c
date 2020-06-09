/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:48:36 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_mult			*create_mult(void)
{
	t_mult		*mult;

	if (!(mult = (t_mult *)malloc(sizeof(t_mult))))
		return (NULL);
	mult->zero = ft_strdup("0");
	mult->preout = "\0";
	mult->out = ft_strdup("0");
	mult->s1 = "\0";
	mult->s2 = "\0";
	mult->hereout = "\0";
	mult->longest = 0;
	mult->carry = 0;
	mult->i = 0;
	return (mult);
}

t_mult			*subloop_mult(t_mult *mult, size_t longest, size_t s, size_t l)
{
	unsigned	temp;

	temp = 0;
	while (l != 0)
	{
		temp = (mult->s1[l - 1] - '0');
		temp = temp * (mult->s2[s - 1] - '0');
		temp = temp + mult->carry;
		if (temp >= 10)
		{
			mult->carry = temp / 10;
			temp = temp % 10;
		}
		else
			mult->carry = 0;
		mult->preout[longest - 1] = temp + '0';
		longest--;
		l--;
	}
	return (mult);
}

char			*mult_loop(size_t l, size_t s, t_mult *mult)
{
	char		*carryc;
	size_t		longest;

	longest = l > s ? l : s;
	mult->preout = ft_strnew(longest);
	carryc = ft_strnew(1);
	mult = subloop_mult(mult, longest, s, l);
	if (mult->carry >= 10)
	{
		carryc[0] = '0' + (mult->carry % 10);
		mult->preout = strjf(carryc, mult->preout, 0, 1);
		mult->carry = mult->carry / 10;
	}
	else if (mult->carry > 0)
	{
		carryc[0] = mult->carry + '0';
		mult->preout = strjf(carryc, mult->preout, 0, 1);
	}
	free(carryc);
	return (mult->preout);
}

char			*ft_mult(char *s1, char *s2)
{
	t_mult		*mult;
	size_t		l;
	size_t		s;
	int			j;

	mult = create_mult();
	l = ft_strlen(s1);
	s = ft_strlen(s2);
	mult->s1 = ft_strdup(s1);
	mult->s2 = ft_strdup(s2);
	while (s != 0)
	{
		mult->hereout = mult_loop(l, s, mult);
		j = 0;
		while (mult->i != j)
		{
			mult->hereout = strjf(mult->hereout, mult->zero, 1, 0);
			j++;
		}
		mult->out = ft_add(mult->out, mult->hereout, 0, 2);
		mult->i++;
		s--;
	}
	clean_mult(mult);
	return (mult->out);
}
