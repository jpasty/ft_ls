/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:47:18 by user              #+#    #+#             */
/*   Updated: 2020/06/05 14:52:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		write_space(char *ptr, int max_len)
{
	int			len;

	if (ptr == NULL)
		return ;
	len = ft_strlen(ptr);
	while (len < max_len)
	{
		ft_printf(" ");
		len++;
	}
}

static mode_t	ls_mode(t_ls *ls, int size)
{
	int			i;

	i = 0;
	while (ls && i < size)
	{
		ls = ls->next;
		i++;
	}
	return (ls->mode);
}

static void		collumns(t_ls *ls, t_columns columns, char **ptr, int i)
{
	int			k;

	k = 1;
	while (k < columns.columns)
	{
		if ((i + columns.word_in_column * k) < columns.max_len_list)
		{
			set_color(ls_mode(ls, i + columns.word_in_column * k),
					ls->flag.g_cap);
			ft_printf("%s", ptr[i + columns.word_in_column * k]);
			ft_putstr(RESET);
			write_space(ptr[i + columns.word_in_column * k],
					columns.max_len);
		}
		k++;
	}
}

void			name_ls(char **ptr, t_columns columns, t_ls *ls)
{
	int			i;

	i = 0;
	while (i < columns.word_in_column)
	{
		set_color(ls_mode(ls, i), ls->flag.g_cap);
		ft_printf("%s", ptr[i]);
		ls->flag.g_cap ? ft_putstr(RESET) : 0;
		write_space(ptr[i], columns.max_len);
		collumns(ls, columns, ptr, i);
		i++;
		ft_printf("\n");
	}
}
