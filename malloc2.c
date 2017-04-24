/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:46:32 by droly             #+#    #+#             */
/*   Updated: 2017/04/24 17:59:45 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list		*split_mem(size_t size, t_list *list, int num)
{
	int		i;

	i = 0;
	list->size = size;
	list->isfree = 1;
	if (num <= 16)
	{
		list->next = &list->start[size];
		list->next->isfree = 0;
		list->next->start = &list->start[size + sizeof(t_list)];
		list->next->next = NULL;
	}
	return (list);
}

void		*add_new2(t_list *list, size_t size, t_list *tmp, t_list *tmp2)
{
	void	*tmp3;
	list->isfree = 1;

	if (list->size >= (sizeof(t_list) + size + 1))
	{
		tmp = &(list->start[size]);
		tmp->start = &(list->start[size + sizeof(t_list)]);
		tmp->floor = list->floor;
		tmp->type = list->type;
		tmp->next = list->next;
		tmp->isfree = 0;
		tmp->size = list->size - (sizeof(t_list) + size);
		list->next = tmp;
		list->size = size;
	}
	tmp3 = list->start;
	list = tmp2;
	return (tmp3);
}

void		add_new3(t_list *list, size_t size)
{
	list->next = &list->start[size];
	list->next->isfree = 0;
	list->next->floor = list->floor;
	list->next->type = list->type;
	list->next->start = &list->start[size + sizeof(t_list)];
	list->next->next = NULL;
	list->next->size = list->size - (size + sizeof(t_list));
	list->size = size;
}

void		*add_new(t_list *list, int page, size_t size, void *tmp)
{
	t_list *tmp2;
	tmp2 = list;
	while (list != NULL)
	{
		if (list->isfree == 0 && list->size >= size && list->next != NULL &&
			(((list->type == 0 && size <= ((unsigned long)(4 * page) /
			100)) || (list->type == 1 && size <= ((unsigned long)(16 *
			page) / 100) && size > ((unsigned long)(4 * page) /
			100))))) 
			return (add_new2(list, size, NULL, tmp2));
		else if (list->isfree == 0 && list->size >= size && (((list->type == 0
		&& size <= ((unsigned long)(4 * page) / 100)) || (list->type
		== 1 && size <= ((unsigned long)(16 * page) / 100) && size >
		((unsigned long)(4 * page) / 100)))))
		{
			list->isfree = 1;
			add_new3(list, size);
			tmp = list->start;
			list = tmp2;
			return (tmp);
		}
		list = list->next;
	}
	list = tmp2;
	return (NULL);
}
