/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 21:57:05 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_error_fd(int fd, char *mes, int code)
{
	write(fd, mes, ft_strlen(mes));
	write(fd, "\n", 1);
	exit(code);
}

void		ft_error(char *mes, int code)
{
	ft_error_fd(2, mes, code);
}

void		ft_errno_fd(int fd, char err, char *mes)
{
	if (err)
		errno = err;
	ft_error_fd(fd, (mes ? mes : strerror(errno)), errno);
}

void		ft_errno(char err, char *mes)
{
	if (err)
		errno = err;
	perror(mes ? mes : strerror(errno));
	exit(errno);
}
