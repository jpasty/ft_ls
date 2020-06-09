/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:49:34 by user              #+#    #+#             */
/*   Updated: 2020/06/07 21:49:06 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/ioctl.h>

double				max_size_name(t_ls *ls)
{
	double			size;
	char			*str;
	char			*next_str;

	size = 0;
	while (ls->next != NULL)
	{
		str = ls->name ? ls->name : ls->path;
		next_str = ls->next->name ? ls->next->name : ls->next->path;
		if ((ft_strlen(str) > ft_strlen(next_str)) && size < ft_strlen((str)))
			size = ft_strlen(str);
		ls = ls->next;
	}
	return (size);
}

int					max_size_list(t_ls *ls)
{
	int		size;

	size = 0;
	while (ls)
	{
		size++;
		ls = ls->next;
	}
	return (size);
}

void				print(t_ls *ls)
{
	struct winsize	window;
	t_columns		columns;
	char			**ptr;

	ioctl(0, TIOCGWINSZ, &window);
	columns.max_len = max_size_name(ls) + BTW_COL;
	columns.max_len_list = max_size_list(ls);
	columns.columns = window.ws_col / columns.max_len;
	if (columns.columns == 0 || ls->flag.one)
		columns.word_in_column = columns.max_len_list;
	else if (columns.max_len_list % columns.columns != 0)
		columns.word_in_column = columns.max_len_list / columns.columns + 1;
	else
		columns.word_in_column = columns.max_len_list / columns.columns;
	ptr = create_arr(ls, columns.max_len_list);
	name_ls(ptr, columns, ls);
	free(ptr);
}
