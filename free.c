/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/05/11 11:58:00 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			find_start(int floor, t_list *tmp2)
{
	t_list	*tmp3;

	g_list = tmp2;
	if (g_list->floor == floor)
	{
		while (g_list != NULL && g_list->floor == floor)
			g_list = g_list->next;
		return (1);
	}
	while (g_list != NULL && g_list->next->floor != floor)
		g_list = g_list->next;
	tmp3 = g_list->next;
	while (tmp3 != NULL && tmp3->floor == floor)
		tmp3 = tmp3->next;
	g_list->next = tmp3;
	g_list = tmp2;
	return (0);
}

int		check_unmap2(t_list *tmp3, int floor, t_list *tmp2, int page)
{
	int i;
	int i2;
	int check;

	i = 0;
	i2 = 0;
	check = 0;
	floor = g_list->floor;
	tmp3 = g_list;
	while (g_list->next != NULL && floor == g_list->floor)
	{
		if (g_list->isfree == 1)
		{
			check = 1;
			while (g_list->next != NULL && g_list->floor == floor)
				g_list = g_list->next;
		}
		if (check == 0)
			g_list = g_list->next;
		i++;
	}
	if (g_list->isfree == 1 && g_list->floor == floor)
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
		g_list = g_list->next;
	i = 0;
	return (1);
}

int			check_unmap(t_list *tmp3)
{
	t_list	*tmp2;
	static int page = -2;

	tmp2 = g_list;
	if (page == -2)
		page = getpagesize();
	while (g_list != NULL)
	{
		if (check_unmap2(tmp3, 0, tmp2, page) == 0)
			return (0);
	}
	g_list = tmp2;
	return (0);
}

int			ft_check(t_list *g_list)
{
	t_list *tmp;
	int check;

	check = 0;
	tmp = g_list;
	while (g_list != NULL)
	{
		if (g_list->type == 2 && g_list->isfree == 0)
			check++;
		g_list = g_list->next;
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
	tmp2 = g_list;
	if (g_list && ptr)
	{
		while (g_list != NULL)
		{
			if (g_list->start == ptr)
			{
				g_list->isfree = 0;
				if (g_list->type == 2)
				{
					if (ft_check(tmp2) <= 1)
						return ;
					tmp3 = g_list;
					find_start(g_list->floor, tmp2);
					if ((munmap(tmp3, tmp3->size + sizeof(t_list) + 1)) == -1)
					{
						g_list->isfree = 1;
						return ;
					}
					return ;
				}
				else if (g_list->type == 1 || g_list->type == 0)
				{
					g_list = tmp2;
					check_unmap(NULL);
					return ;
				}
				g_list = tmp2;
				return ;
			}
			g_list = g_list->next;
		}
	}
	g_list = tmp2;
}
