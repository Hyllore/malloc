/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/05/09 16:50:01 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			find_start(int floor, t_list *tmp2)
{
	t_list	*tmp3;

	list = tmp2;
	if (list->floor == floor)
	{
		while (list != NULL && list->floor == floor)
			list = list->next;
		return (1);
	}
	while (list != NULL && list->next->floor != floor)
		list = list->next;
	tmp3 = list->next;
	while (tmp3 != NULL && tmp3->floor == floor)
		tmp3 = tmp3->next;
	list->next = tmp3;
	list = tmp2;
	return (0);
}

int			check_unmap(t_list *tmp3)
{
	int		check;
	int		floor;
	int		i;
	int		i2;
	t_list	*tmp2;
	static int page = -2;

	i2 = 0;
	tmp2 = list;
	i = 0;
	check = 0;
	if (page == -2)
		page = getpagesize();
	while (list != NULL)
	{
		floor = list->floor;
		tmp3 = list;
		while (list->next != NULL && floor == list->floor)
		{
			if (list->isfree == 1)
			{
				check = 1;
				while (list->next != NULL && list->floor == floor)
					list = list->next;
			}
			if (check == 0)
				list = list->next;
			i++;
		}
		if (list->isfree == 1 && list->floor == floor)
			check = 1;
		if (check == 0 && tmp3->type == 0 && i >= 10)
		{
			find_start(tmp3->floor, tmp2);
			if (munmap(tmp3, ((8 * page) + (sizeof(t_list) * 100))) == -1)
			{
				return (0);
			}
			return (i2);
		}
		if (check == 0 && tmp3->type == 1 && i >= 10)
		{
			find_start(tmp3->floor, tmp2);
			if (munmap(tmp3, ((32 * page) + (sizeof(t_list) * 100))) == -1)
			{
				return (0);
			}
			return (i2);
		}
		check = 0;
		if (i == 0)
			list = list->next;
		i = 0;
	}
	list = tmp2;
	return (0);
}

int			ft_check(t_list *list)
{
	t_list *tmp;
	int check;

	check = 0;
	tmp = list;
	while (list != NULL)
	{
		if (list->type == 2 && list->isfree == 0)
			check++;
		list = list->next;
	}
	return (check);
}

void		free(void *ptr)
{
	t_list	*tmp2;
	t_list	*tmp3;
	int		i;

	i = 0;
	tmp3 = NULL;
	tmp2 = list;
	if (list && ptr)
	{
		while (list != NULL)
		{
			if (list->start == ptr)
			{
				list->isfree = 0;
				if (list->type == 2)
				{
					if (ft_check(tmp2) <= 1)
						return ;
					tmp3 = list;
					find_start(list->floor, tmp2);
					if ((munmap(tmp3, tmp3->size + sizeof(t_list) + 1)) == -1)
					{
						list->isfree = 1;
						return ;
					}
					return ;
				}
				else if (list->type == 1 || list->type == 0)
				{
					list = tmp2;
					check_unmap(NULL);
					return ;
				}
				list = tmp2;
				return ;
			}
			list = list->next;
		}
	}
	list = tmp2;
}
