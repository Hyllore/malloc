/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 15:36:34 by droly             #+#    #+#             */
/*   Updated: 2017/05/12 15:40:42 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_unmap(t_list *tmp3)
{
	t_list		*tmp2;
	static int	page = -2;

	tmp2 = g_list;
	if (page == -2)
		page = getpagesize();
	while (g_list != NULL)
	{
		if (check_unmap2(tmp3, g_list->floor, tmp2, page) == 0)
			return (0);
	}
	g_list = tmp2;
	return (0);
}

int				ft_check(t_list *g_list)
{
	t_list		*tmp;
	int			check;

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
