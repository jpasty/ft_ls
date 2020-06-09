/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:35:02 by user              #+#    #+#             */
/*   Updated: 2020/06/09 16:56:16 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_ls_node(t_ls *entry, t_ls **ls)
{
	t_ls	*tmp;

	if (!(tmp = (t_ls *)malloc(sizeof(t_ls))))
	{
		ft_printf("%s", strerror(errno));
		return ;
	}
	if (entry && ls)
	{
		*tmp = *entry;
		tmp->next = *ls;
		*ls = tmp;
	}
}

void		free_list(t_ls *ls)
{
	t_ls	*cur;
	t_ls	*next;

	cur = ls;
	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur->path);
		free(cur->tm);
		free(cur->uname);
		free(cur->gname);
		free(cur->link);
		free(cur->l_to_dir);
		free(cur->chmod);
		free(cur);
		cur = next;
	}
}

int			input_processing(t_flag flag, int ac, char **av)
{
	t_ls	*fls;
	t_ls	*dls;
	t_ls	entry;
	int		i;

	fls = NULL;
	dls = NULL;
	i = 0;
	while (i < ac)
	{
		if (!init_struct(&entry, flag, ft_strdup(av[i++]), 1))
			continue ;
		if (!entry.flag.d && (S_ISDIR(entry.mode) || entry.l_to_dir))
			add_ls_node(&entry, &dls);
		else
			add_ls_node(&entry, &fls);
	}
	merge_sort(&fls);
	merge_sort(&dls);
	ft_ls(fls, 0, 0);
	(fls && dls) ? ft_putchar('\n') : 0;
	free_list(fls);
	ft_ls(dls, !flag.d, (dls && (fls || dls->next)) || flag.r_cap);
	free_list(dls);
	return (0);
}

int			main(int ac, char **av)
{
	t_flag	flag;
	char	*cd;
	int 	ret;

	cd = CURR_DIR;
	collect_flags(&flag, &ac, &av);
	if (ac)
		ret = input_processing(flag, ac, av);
	else
		ret = input_processing(flag, 1, &cd);
	return (ret);
}
