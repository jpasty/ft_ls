/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 15:00:58 by user              #+#    #+#             */
/*   Updated: 2020/06/08 20:47:08 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*lpath(char *linkname, mode_t mode)
{
	int			len;
	char		buf[MAX_PATH];
	char		*res;

	if (S_ISLNK(mode))
	{
		errno = 0;
		if ((len = readlink(linkname, buf, MAX_PATH)) < 0)
		{
			ft_printf("ft_ls: cannot read symbolic link \'%s\': %s\n", linkname,
				strerror(errno));
			return (NULL);
		}
		buf[len] = '\0';
		res = ft_strdup(buf);
		return (res);
	}
	return (NULL);
}

static int		digit_length(long num)
{
	if (num < 10)
		return (1);
	return (1 + digit_length(num / 10));
}

static t_print	init_print(t_ls **ls, int only_group_name)
{
	t_print		p;
	t_ls		*dt;

	dt = *ls;
	p.max_mode = ft_strlen(dt->chmod);
	p.max_nlink = digit_length(dt->nlink);
	p.max_uname = only_group_name ? 0 : ft_strlen(dt->uname);
	p.max_gname = (int)ft_strlen(dt->gname);
	p.max_size = digit_length(dt->size);
	p.max_mjr = (S_ISBLK(dt->mode) || S_ISCHR(dt->mode)) ?
			digit_length(mjr(dt)) : 0;
	p.max_mnr = (S_ISBLK(dt->mode) || S_ISCHR(dt->mode)) ?
			digit_length(mnr(dt)) : 0;
	if (p.max_mjr && p.max_mnr)
	{
		if (p.max_size < (p.max_mjr + p.max_mnr + 2))
			p.max_size = p.max_mjr + p.max_mnr + 2;
		else
			p.max_mjr = p.max_size - p.max_mnr - 2;
	}
	*ls = (*ls)->next;
	return (p);
}

static void		in_dev_dir(t_print *t, t_print *p)
{
	(*p).max_mjr = (*t).max_mjr > (*p).max_mjr ? (*t).max_mjr : (*p).max_mjr;
	(*p).max_mnr = (*t).max_mnr > p->max_mnr ? (*t).max_mnr : p->max_mnr;
	if ((*p).max_size < ((*p).max_mjr + (*p).max_mnr + 2))
		(*p).max_size = (*p).max_mjr + (*p).max_mnr + 2;
	else
		(*p).max_mjr = (*p).max_size - (*p).max_mnr - 2;
}

t_print			print_utils(t_ls *ls)
{
	t_print		p;
	t_print		tmp;

	p = init_print(&ls, !ls->flag.g);
	while (ls)
	{
		if ((tmp.max_mode = ft_strlen(ls->chmod)) > p.max_mode)
			p.max_mode = tmp.max_mode;
		if ((tmp.max_nlink = digit_length(ls->nlink)) > p.max_nlink)
			p.max_nlink = tmp.max_nlink;
		if ((tmp.max_uname = ft_strlen(ls->uname)) > p.max_uname && !ls->flag.g)
			p.max_uname = tmp.max_uname;
		if ((tmp.max_gname = ft_strlen(ls->gname)) > p.max_gname)
			p.max_gname = tmp.max_gname;
		if ((tmp.max_size = digit_length(ls->size)) > p.max_size)
			p.max_size = tmp.max_size;
		tmp.max_mjr = (S_ISBLK(ls->mode) || S_ISCHR(ls->mode)) ?
				digit_length(mjr(ls)) : 0;
		tmp.max_mnr = (S_ISBLK(ls->mode) || S_ISCHR(ls->mode)) ?
				digit_length(mnr(ls)) : 0;
		if (tmp.max_mjr && tmp.max_mnr)
			in_dev_dir(&tmp, &p);
		ls = ls->next;
	}
	return (p);
}
