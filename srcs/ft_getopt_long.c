/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:29:26 by user              #+#    #+#             */
/*   Updated: 2020/06/06 22:38:31 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				find_val(t_input *input, t_lopt *o, t_opt **opt)
{
	int			retval;

	if (o->flag)
		*(o->flag) = o->val;
	retval = o->flag ? 0 : o->val;
	if (o->hasarg != NO_ARG)
	{
		(*opt)->optarg = ft_strchr(input->av[(*opt)->optind], '=');
		if ((*opt)->optarg != NULL)
			((*opt)->optarg)++;
		if (o->hasarg == REQ_ARG)
		{
			if ((*opt)->optarg == NULL && ++((*opt)->optind) < input->ac)
				(*opt)->optarg = input->av[(*opt)->optind];
			if ((*opt)->optarg == NULL)
				retval = ':';
		}
	}
	else if (ft_strchr(input->av[(*opt)->optind], '='))
		retval = '?';
	return (retval);
}

int				find_matches(t_lopt *o, t_lopt **match, t_input input, int arg)
{
	int			num_matches;
	const char	*curr_arg;
	size_t		arg_name_length;

	num_matches = 0;
	curr_arg = input.av[arg] + 2;
	arg_name_length = ft_strcspn(curr_arg, "=");
	while (o->name)
	{
		if (ft_strncmp(o->name, curr_arg, arg_name_length) == 0
			&& o->name[arg_name_length] == '\0')
		{
			*match = o;
			num_matches++;
		}
		o++;
	}
	return (num_matches);
}

int				get_lopt(t_input input, t_opt *opt, t_lopt *lopt, int *longind)
{
	t_lopt		*o;
	t_lopt		*match;
	int			retval;

	o = lopt;
	match = NULL;
	if (opt->optind >= input.ac)
		return (-1);
	if (ft_strlen(input.av[opt->optind]) < 3 ||
		ft_strncmp(input.av[opt->optind], "--", 2) != 0)
		return (ft_getopt(input, opt));
	if (find_matches(o, &match, input, opt->optind) == 1)
	{
		if (longind)
			*longind = (int)(match - lopt);
		retval = find_val(&input, match, &opt);
	}
	else
	{
		retval = '?';
		opt->optopt = input.av[opt->optind];
	}
	++(opt->optind);
	return (retval);
}

int				ft_getopt_long(t_input data, t_opt **opt,
							const t_lopt *lopt, int *lind)
{
	int			ret;

	*opt = set_start_opt_val(*opt);
	ret = get_lopt(data, *opt, lopt, lind);
	return (ret);
}
