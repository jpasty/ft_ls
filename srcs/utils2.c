/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:57:32 by user              #+#    #+#             */
/*   Updated: 2020/06/05 16:37:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned		mjr(t_ls *ls)
{
	return ((unsigned)(((ls->rdev) >> 24) & 0xff));
}

unsigned		mnr(t_ls *ls)
{
	return ((unsigned)((ls->rdev) & 0xffff));
}

char			set_zero_mode(mode_t mode)
{
	char		file_mode;

	if (S_ISREG(mode))
		file_mode = '-';
	else if (S_ISBLK(mode))
		file_mode = 'b';
	else if (S_ISCHR(mode))
		file_mode = 'c';
	else if (S_ISDIR(mode))
		file_mode = 'd';
	else if (S_ISFIFO(mode))
		file_mode = 'p';
	else if (S_ISLNK(mode))
		file_mode = 'l';
	else if (S_ISSOCK(mode))
		file_mode = 's';
	else
		file_mode = '?';
	return (file_mode);
}

char			ft_acl(t_ls *ls)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;
	char		chr;

	xattr = 0;
	acl = acl_get_link_np(ls->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(ls->path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		chr = '@';
	else if (acl != NULL)
		chr = '+';
	else
		chr = '\0';
	acl_free(acl);
	return (chr);
}
