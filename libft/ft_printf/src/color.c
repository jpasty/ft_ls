/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:44:41 by lseema            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		colorize(const char *s)
{
	short int	i;
	char		color[8];
	int			offset;
	char		*clr;

	i = 0;
	while (s[i] != '}' && s[i] != '\0' && i <= 6)
	{
		*(color + i) = ft_toupper(s[i]);
		i++;
	}
	color[i] = '\0';
	clr = ft_strdup(color);
	offset = (s[i] == '}' && put_color(clr)) ? (i + 2) : 0;
	free(clr);
	return (offset);
}

int		put_color(char *color)
{
	if (!ft_strcmp(color, "EOC"))
		ft_putstr(RESET);
	else if (!ft_strcmp(color, "RED"))
		ft_putstr(RED);
	else if (!ft_strcmp(color, "GREEN"))
		ft_putstr(GREEN);
	else if (!ft_strcmp(color, "YELLOW"))
		ft_putstr(YELLOW);
	else if (!ft_strcmp(color, "BLUE"))
		ft_putstr(BLUE);
	else if (!ft_strcmp(color, "WHITE"))
		ft_putstr(WHITE);
	else if (!ft_strcmp(color, "BLACK"))
		ft_putstr(BLACK);
	else if (!ft_strcmp(color, "CYAN"))
		ft_putstr(CYAN);
	else if (!ft_strcmp(color, "MAGENTA"))
		ft_putstr(MAGENTA);
	else
		return (0);
	return (1);
}
