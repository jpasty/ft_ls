/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:31:32 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_calc		*create_calc(void)
{
	t_calc	*calc;

	if (!(calc = (t_calc *)malloc(sizeof(t_calc))))
		return (NULL);
	calc->zero = "0";
	calc->ten = "10";
	calc->one = "1";
	calc->rem = ft_strdup("10");
	calc->out = ft_strdup("");
	return (calc);
}

char		*ft_rem(char *val, t_calc *calc)
{
	char	*xl;
	char	*k;
	char	*temp;
	int		i;

	i = 2;
	k = ft_strdup("1");
	xl = ft_strdup("1");
	while (ft_chararcmp(calc->rem, xl) >= 0 && i < 10)
	{
		k = ft_add(k, ft_strdup("1"), 0, 2);
		temp = xl;
		xl = ft_mult(val, k);
		free(temp);
		i++;
	}
	if ((i == 10 && ft_chararcmp(calc->rem, xl) <= 0) || i != 10)
		k = ft_subtract(k, calc->one);
	free(xl);
	return (k);
}

char		*negs_loop(int f, size_t len, t_calc *calc, char *val)
{
	int		w;
	char	*temp;

	w = 0;
	if (f == 0)
	{
		while (len != 0)
		{
			calc->out = strjf(calc->out, calc->zero, 1, 0);
			temp = calc->rem;
			calc->rem = ft_mult(calc->rem, calc->ten);
			free(temp);
			len--;
		}
	}
	while (ft_chararcmp(calc->rem, val) <= 0)
	{
		w++;
		temp = calc->rem;
		calc->rem = ft_mult(calc->rem, calc->ten);
		free(temp);
		if (w > 1)
			calc->out = strjf(calc->out, calc->zero, 1, 0);
	}
	return (calc->out);
}

char		*ft_negs(char *res)
{
	t_calc	*calc;
	char	*val;
	int		f;
	size_t	len;
	char	*temp;

	calc = create_calc();
	f = 0;
	len = ft_strlen(res) - 1;
	while (ft_chararcmp(calc->rem, calc->zero) != 0)
	{
		calc->out = negs_loop(f, len, calc, res);
		val = ft_rem(res, calc);
		f = 1;
		temp = ft_mult(res, val);
		calc->rem = ft_subtract(calc->rem, temp);
		free(temp);
		calc->out = strjf(calc->out, val, 1, 1);
	}
	free(calc->rem);
	val = calc->out;
	free(calc);
	free(res);
	return (val);
}
