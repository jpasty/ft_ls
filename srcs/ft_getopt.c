/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:33:18 by user              #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				no_more_options(char **optcursor)
{
	*optcursor = NULL;
	return (-1);
}

void			opt_has_arg(t_input *input, t_opt **opt, char **optcursor)
{
	if ((*opt)->optdecl)
	{
		if ((*opt)->optdecl[1] == ':')
		{
			(*opt)->optarg = ++(*optcursor);
			if (*((*opt)->optarg) == '\0')
			{
				if ((*opt)->optdecl[2] != ':')
				{
					if (++((*opt)->optind) < input->ac)
						(*opt)->optarg = input->av[(*opt)->optind];
					else
					{
						(*opt)->optarg = NULL;
						(*opt)->optchar = (FLAGS[0] == ':') ? ':' : '?';
					}
				}
				else
					(*opt)->optarg = NULL;
			}
			*optcursor = NULL;
		}
	}
	else
		(*opt)->optchar = '?';
}

int				ft_get_opt(t_input *input, t_opt *opt)
{
	static char	*optcursor = NULL;

	opt->optarg = NULL;
	if (opt->optind >= input->ac || input->av[opt->optind] == NULL ||
		*(input->av)[opt->optind] != '-'
		|| ft_strcmp(input->av[opt->optind], "-") == 0)
		return (no_more_options(&optcursor));
	if (ft_strcmp(input->av[opt->optind], "--") == 0)
	{
		(opt->optind)++;
		return (no_more_options(&optcursor));
	}
	if (optcursor == NULL || *optcursor == '\0')
		optcursor = input->av[opt->optind] + 1;
	opt->optchar = *optcursor;
	opt->optopt = optcursor;
	opt->optdecl = ft_strchr(FLAGS, opt->optchar);
	opt_has_arg(input, &opt, &optcursor);
	if (optcursor == NULL || *(++optcursor) == '\0')
		(opt->optind)++;
	return (opt->optchar);
}

t_opt			*set_start_opt_val(t_opt *opt)
{
	if (!opt)
	{
		if (!(opt = (t_opt *)malloc(sizeof(t_opt))))
			exit(-1);
		opt->optarg = NULL;
		opt->optdecl = NULL;
		opt->optchar = -1;
		opt->optind = 1;
		return (opt);
	}
	else
		return (opt);
}

int				ft_getopt(t_input input, t_opt *opt)
{
	int			ret;

	opt = set_start_opt_val(opt);
	ret = ft_get_opt(&input, opt);
	return (ret);
}
