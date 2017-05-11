/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:46:32 by droly             #+#    #+#             */
/*   Updated: 2017/05/11 10:40:31 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		add_new3(t_list *g_list, size_t size)
{
	g_list->next = &g_list->start[size];
	g_list->next->isfree = 0;
	g_list->next->floor = g_list->floor;
	g_list->next->type = g_list->type;
	g_list->next->start = &g_list->start[size + sizeof(t_list)];
	g_list->next->next = NULL;
	g_list->next->size = g_list->size - (size + sizeof(t_list));
	g_list->size = size;
}

t_list		*check_size(t_list *g_list, size_t size, int page)
{
	if (size <= (unsigned long)((8 * page) / 100))
		g_list = begin_new(g_list, 8, size, 0);
	if (size <= (unsigned long)((32 * page) / 100) && size >
			(unsigned long)((8 * page) / 100))
		g_list = begin_new(g_list, 32, size, 1);
	if (size > (unsigned long)((32 * page) / 100))
		g_list = begin_new(g_list, size + sizeof(t_list), size, 2);
	return (g_list);
}

void		*addnewtmp2(t_list *g_list, void *tmp, t_list *tmp2, size_t size)
{
	g_list->isfree = 1;
	add_new3(g_list, size);
	tmp = g_list->start;
	g_list = tmp2;
	return (tmp);
}

void		*addnewtmp1(t_list *g_list, void *tmp, t_list *tmp2)
{
	g_list->isfree = 1;
	tmp = g_list->start;
	g_list = tmp2;
	return (tmp);
}

void		*add_new(t_list *g_list, int page, size_t size, void *tmp)
{
	t_list	*tmp2;

	tmp2 = g_list;
	while (g_list != NULL)
	{
		if (g_list->isfree == 0 && g_list->size >= size && g_list->next != NULL
			&& (((g_list->type == 0 && size <= ((unsigned long)(8 * page) /
			100)) || (g_list->type == 1 && size <= ((unsigned long)(32 *
			page) / 100) && size > ((unsigned long)(8 * page) /
			100)))))
			return (add_new2(g_list, size, NULL, tmp2));
		else if (g_list->isfree == 0 && g_list->size >= size && (((g_list->type
		== 0 && size <= ((unsigned long)(8 * page) / 100)) || (g_list->type
		== 1 && size <= ((unsigned long)(32 * page) / 100) && size >
		((unsigned long)(8 * page) / 100)))))
			return (addnewtmp2(g_list, tmp, tmp2, size));
		else if (g_list->isfree == 0 && g_list->size >= size && g_list->type
		== 2 && size > ((unsigned long)(32 * page) / 100))
			return (addnewtmp1(g_list, tmp, tmp2));
		g_list = g_list->next;
	}
	g_list = tmp2;
	return (NULL);
}
