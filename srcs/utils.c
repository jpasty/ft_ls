/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 15:03:07 by user              #+#    #+#             */
/*   Updated: 2020/06/08 15:56:12 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*get_user_name(uid_t user_id)
{
	t_user	*usr;
	char	*uname;

	if (!(usr = getpwuid(user_id)))
	{
		ft_printf("Can't get struct for user: %d\n", user_id);
		return (ft_strdup(""));
	}
	if (!(uname = ft_strdup(usr->pw_name)))
	{
		ft_printf("ft_ls: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (uname);
}

char		*get_group_name(gid_t group_id)
{
	t_group	*grp;
	char	*gname;

	if (!(grp = getgrgid(group_id)))
	{
		ft_printf("Can't get struct for group: %d\n", group_id);
		return (ft_strdup(""));
	}
	if (!(gname = ft_strdup(grp->gr_name)))
	{
		ft_printf("ft_ls: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (gname);
}

char		*get_tm(t_time t)
{
	char	*tm;
	char	*year;
	char	*date;
	char	*fmt;

	tm = ctime(&t.tv_sec);
	if ((time(NULL) > t.tv_sec + 15552000))
	{
		date = ft_strsub(tm, 4, 7);
		year = ft_strsub(tm, 19, 5);
		fmt = ft_strjoin(date, year);
		free(date);
		free(year);
	}
	else
		fmt = ft_strsub(tm, 4, 12);
	return (fmt);
}

int64_t		total_blk(t_ls *ls)
{
	int64_t total;

	total = 0;
	if (ls)
	{
		while (ls)
		{
			total += ls->block;
			ls = ls->next;
		}
	}
	return (total);
}

char		**create_arr(t_ls *ls, int max_len_list)
{
	char	**ptr;
	int		i;

	if (!(ptr = (char **)malloc(sizeof(char *) * max_len_list + 1)))
		return (NULL);
	i = 0;
	while (ls)
	{
		ptr[i] = ls->name ? ls->name : ls->path;
		ls = ls->next;
		i++;
	}
	return (ptr);
}
