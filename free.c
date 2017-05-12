/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/05/12 15:42:58 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				find_start(int floor, t_list *tmp2)
{
	t_list		*tmp3;

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

int				check_unmap3(int check, int i, int floor[static 2],
		t_list *tmp2)
{
	t_list		*tmp3;

	tmp3 = tmp2;
	if (g_list->isfree == 1 && g_list->floor == floor[0])
		check = 1;
	if (check == 0 && tmp3->type == 0 && i >= 10)
	{
		find_start(tmp3->floor, tmp2);
		if (munmap(tmp3, ((8 * floor[1]) + (sizeof(t_list) * 100))) == -1)
			return (0);
		return (0);
	}
	if (check == 0 && tmp3->type == 1 && i >= 10)
	{
		find_start(tmp3->floor, tmp2);
		if (munmap(tmp3, ((32 * floor[1]) + (sizeof(t_list) * 100))) == -1)
			return (0);
		return (0);
	}
	return (1);
}

int				check_unmap2(t_list *tmp3, int floor, t_list *tmp2, int page)
{
	int			i;
	int			check;

	i = 0;
	check = 0;
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
	if (check_unmap3(check, i, ((int[2]){floor, page}), tmp2) == 0)
		return (0);
	check = 0;
	if (i == 0)
		g_list = g_list->next;
	i = 0;
	return (1);
}

int				free2(void *ptr, t_list *tmp3, t_list *tmp2)
{
	if (g_list->start == ptr)
	{
		g_list->isfree = 0;
		if (g_list->type == 2)
		{
			if (ft_check(tmp2) <= 1)
				return (1);
			tmp3 = g_list;
			find_start(g_list->floor, tmp2);
			if ((munmap(tmp3, tmp3->size + sizeof(t_list) + 1)) == -1)
				g_list->isfree = 1;
			return (1);
		}
		else if (g_list->type == 1 || g_list->type == 0)
		{
			g_list = tmp2;
			check_unmap(NULL);
			return (1);
		}
		g_list = tmp2;
		return (1);
	}
	return (0);
}

void			free(void *ptr)
{
	t_list		*tmp2;

	tmp2 = g_list;
	if (g_list && ptr)
	{
		while (g_list != NULL)
		{
			if (free2(ptr, NULL, tmp2) == 1)
				return ;
			g_list = g_list->next;
		}
	}
	g_list = tmp2;
}
