/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:55:47 by user              #+#    #+#             */
/*   Updated: 2020/06/09 14:29:58 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_FT_GETOPT_H
# define LS_FT_GETOPT_H

# include "libft.h"

# define FLAGS		"1adfG::glRrtu"

# define NO_ARG		0
# define REQ_ARG	1
# define OPT_ARG	2

# define COLOR_OFF	0
# define COLOR_ON	1

typedef struct			s_opt
{
	char				*optarg;
	int					optind;
	int					optchar;
	char				*optdecl;
	char				*optopt;
}						t_opt;

typedef const struct	s_lopt
{
	const char			*name;
	int					hasarg;
	int					*flag;
	int					val;
}						t_lopt;

typedef struct			s_input
{
	int					ac;
	char				**av;
}						t_input;

typedef struct			s_flag
{
	int					one;
	int					a;
	int					d;
	int					f;
	int					g_cap;
	int					g;
	int					l;
	int					r_cap;
	int					r;
	int					t;
	int					u;
}						t_flag;

t_opt					*set_start_opt_val(t_opt *opt);
int						ft_getopt(t_input inpt, t_opt *opt);
int						ft_getopt_long(t_input data, t_opt **opt,
							const t_lopt *lopt, int *lind);

#endif
