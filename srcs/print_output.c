/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:37:33 by user              #+#    #+#             */
/*   Updated: 2020/06/09 17:02:38 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int 		work_with_link(t_ls *ls)
{
	ls->link = lpath(ls->path, ls->mode);
	if (!(link_to_dir(ls)))
	{
		free(ls->name);
		free(ls->path);
		free(ls->tm);
		free(ls->uname);
		free(ls->gname);
		free(ls->link);
		free(ls->l_to_dir);
		free(ls->chmod);
		return (0);
	}
	return (1);
}

char 		*get_link_to_dir(t_ls *ls)
{
	char	*path;
	int		l;

	l = ft_strlen(ls->path);
	if (!l && !ls->path)
		return (NULL);
	if (ls->link && ls->link[0] != '/')
	{
		while (ls->path[l - 1] != '/')
			l--;
		if (!(path = ft_strsub(ls->path, 0, l)) ||
			!(ls->l_to_dir = ft_strjoin(path, ls->link)))
		{
			free(path);
			ft_error("Can't allocate memory", 2);
		}
		free(path);
	}
	else
	{
		if (!(ls->l_to_dir = ft_strdup(ls->link)))
			ft_error("Can't allocate memory", 2);
	}
	return (ls->l_to_dir);
}

void		print_long_info(t_ls *ls, t_print t)
{
	if (!ls->flag.g)
		ft_printf("%-*s %*u %-*s %-*s ", t.max_mode, ls->chmod, t.max_nlink,
		ls->nlink, t.max_uname, ls->uname, t.max_gname, ls->gname);
	else
		ft_printf("%*s %*u %-*s ", t.max_mode, ls->chmod, t.max_nlink,
		ls->nlink, t.max_gname, ls->gname);
	if (S_ISBLK(ls->mode) || S_ISCHR(ls->mode))
		ft_printf("%*u, %*u %s ", t.max_mjr, mjr(ls),
				t.max_mnr, mnr(ls), ls->tm);
	else
		ft_printf("%*lu %s ", t.max_size, ls->size, ls->tm);
}

void		print_output(t_ls *ls)
{
	t_print	t;

	if (!ls->flag.l && !ls->flag.g)
	{
		print(ls);
		return ;
	}
	t = print_utils(ls);
	while (ls)
	{
		print_long_info(ls, t);
		set_color(ls->mode, ls->flag.g_cap);
		ft_printf("%s", ls->name ? ls->name : ls->path);
		ft_putstr(RESET);
		S_ISLNK(ls->mode) ? ft_printf(" -> %s\n", ls->link) : ft_putchar('\n');
		ls = ls->next;
	}
}
