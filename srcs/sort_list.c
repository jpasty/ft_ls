/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:52:42 by user              #+#    #+#             */
/*   Updated: 2020/06/06 22:35:22 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			entry_compare(t_ls *a, t_ls *b)
{
	int		cmp;

	cmp = 0;
	if (a->flag.f)
		return (1);
	if (a->flag.t)
	{
		if (!(cmp = b->time.tv_sec - a->time.tv_sec))
			cmp = b->time.tv_nsec - a->time.tv_nsec;
	}
	if (!cmp)
		cmp = ft_strcmp(a->path, b->path);
	return (a->flag.r ? 0 - cmp : cmp);
}

t_ls		*merge(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (entry_compare(a, b) <= 0)
	{
		result = a;
		result->next = merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next);
	}
	return (result);
}

void		devide(t_ls *head, t_ls **a, t_ls **b)
{
	t_ls	*fast;
	t_ls	*slow;

	slow = head;
	fast = head->next;
	while (fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next;
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

void		merge_sort(t_ls **list_to_sort)
{
	t_ls	*head;
	t_ls	*a;
	t_ls	*b;

	head = *list_to_sort;
	if ((head == NULL) || (head->next == NULL))
		return ;
	devide(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*list_to_sort = merge(a, b);
}
