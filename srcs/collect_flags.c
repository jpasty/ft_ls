/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 22:04:36 by user              #+#    #+#             */
/*   Updated: 2020/06/08 17:11:57 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				invalid_option(t_opt *opt)
{
	ft_printf("ft_ls: illegal option -- \'%s\'\n", opt->optopt);
	ft_printf("usage: ls [-GRadfglrtu1] [file ...]\n");
	ft_printf("or: [--all] [--directory] ");
	ft_printf("[--color[={on, off}]] [--recursive] [--reverse]\n");
	free(opt);
	exit(2);
}

void				set_flag(int rez, t_flag *flag)
{
	if (rez == '1')
		flag->one = 1;
	if (rez == 'a')
		flag->a = 1;
	else if (rez == 'd')
		flag->d = 1;
	else if (rez == 'f')
	{
		flag->a = 1;
		flag->f = 1;
	}
	else if (rez == 'g')
		flag->g = 1;
	else if (rez == 'l')
		flag->l = 1;
	else if (rez == 'R')
		flag->r_cap = 1;
	else if (rez == 'r')
		flag->r = 1;
	else if (rez == 't')
		flag->t = 1;
	else
		flag->u = 1;
}

t_lopt				*set_lopt(void)
{

	static t_lopt	lopt[] = {
						{"all", NO_ARG, NULL, 'a'},
						{"color", OPT_ARG, NULL, 'G'},
						{"directory", NO_ARG, NULL, 'd'},
						{"long", NO_ARG, NULL, 'l'},
						{"only-group", NO_ARG, NULL, 'g'},
						{"recursive", NO_ARG, NULL, 'R'},
						{"reverse", NO_ARG, NULL, 'r'},
						{NULL, 0, NULL, 0}
						};
	return (lopt);
}

void				reset_flags(t_flag *flag)
{
	flag->one = 0;
	flag->a = 0;
	flag->d = 0;
	flag->f = 0;
	flag->g_cap = COLOR_OFF;
	flag->g = 0;
	flag->l = 0;
	flag->r_cap = 0;
	flag->r = 0;
	flag->t = 0;
	flag->u = 0;
}

void				collect_flags(t_flag *flag, int *ac, char ***av)
{
	t_opt			*opt;
	t_lopt			*lopt;
	int				rez;
	t_input			tmp;

	reset_flags(flag);
	opt = NULL;
	lopt = set_lopt();
	tmp.av = *av;
	tmp.ac = *ac;
	while ((rez = ft_getopt_long(tmp, &opt, lopt, NULL)) != -1)
	{
		if (rez == '?')
			invalid_option(opt);
		if (rez == 'G')
		{
			flag->g_cap = is_colorize(opt->optarg);
			continue ;
		}
		set_flag(rez, flag);
	}
	*av += opt->optind;
	*ac -= opt->optind;
	free(opt);
}
