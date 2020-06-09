/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:18:13 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	color_reg(mode_t mode)
{
	if (((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH)) &&
	!((S_ISUID & mode) || (S_ISGID & mode)))
		ft_putstr(GREEN);
	else
	{
		if (S_ISGID & mode)
		{
			if (S_ISUID & mode)
			{
				ft_putstr("\x1b[37;41m");
				return ;
			}
			ft_putstr("\x1b[30;43m");
		}
	}
}

void	color_dir(mode_t mode)
{
	if ((S_IWOTH & mode))
		ft_putstr("\x1b[34;42m");
	else
	{
		if (mode & S_ISVTX)
			ft_putstr("\x1b[37;44m");
		else
			ft_putstr(BLUE);
	}
}

void	set_color(mode_t mode, int do_color)
{
	if (!do_color)
		return ;
	if (S_ISREG(mode))
		color_reg(mode);
	if (S_ISDIR(mode))
		color_dir(mode);
	if (S_ISLNK(mode))
		ft_putstr(CYAN);
	if (S_ISFIFO(mode))
		ft_putstr(RED);
	if (S_ISSOCK(mode))
		ft_putstr(MAGENTA);
	if (S_ISCHR(mode) || S_ISBLK(mode))
		ft_putstr(YELLOW);
}

int		is_colorize(char *opt_arg)
{
	int	i;

	i = 0;
	if (opt_arg)
	{
		while (opt_arg[i])
		{
			opt_arg[i] = ft_tolower(opt_arg[i]);
			i++;
		}
		return (ft_strcmp(opt_arg, "on") == 0 ? COLOR_ON : COLOR_OFF);
	}
	else
		return (COLOR_ON);
}