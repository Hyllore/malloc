/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:46:32 by droly             #+#    #+#             */
/*   Updated: 2017/03/27 13:58:43 by droly            ###   ########.fr       */
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

void		*add_new2(t_list *list, size_t size, t_list *tmp)
{
	list->isfree = 1;
	if (list->size >= (sizeof(t_list) + size + 1))
	{
		tmp = &list->start[size];
		tmp->isfree = 0;
		tmp->next = list->next;
		tmp->start = &tmp[sizeof(t_list)];
		tmp->floor = list->floor;
		tmp->type = list->type;
//		printf("size remaining hey: %lu\n", list->size - (size +
//					sizeof(t_list)));
		tmp->size = list->size - (sizeof(t_list) + size);
		tmp = &list->start[size];
		list->next = tmp;
		list->size = size;
	}
	return (list->start);
}

void		*add_new(t_list *list, t_list *tmp2, size_t size)
{
	void	*tmp;

	tmp2 = list;
	while (list != NULL)
	{
		if (list->isfree == 0 && list->size >= size && list->next != NULL &&
		(((list->type == 0 && size <= ((unsigned long)(4 * getpagesize()) /
		100)) || (list->type == 1 && size <= ((unsigned long)(16 *
		getpagesize()) / 100) && size > ((unsigned long)(4 * getpagesize()) /
		100)))))
			return (add_new2(list, size, NULL));
		else if (list->isfree == 0 && list->size >= size && (((list->type == 0
		&& size <= ((unsigned long)(4 * getpagesize()) / 100)) || (list->type
		== 1 && size <= ((unsigned long)(16 * getpagesize()) / 100) && size >
		((unsigned long)(4 * getpagesize()) / 100)))))
		{
			list->isfree = 1;
			if (list->size >= (sizeof(t_list) + size + 1))
			{
				list->next = &list->start[size];
				list->next->isfree = 0;
				list->next->floor = list->floor;
				list->next->type = list->type;
				list->next->start = &list->start[size + sizeof(t_list)];
				list->next->next = NULL;
//				printf("size remaining: %lu\n", list->size - (size +
//							sizeof(t_list)));
				list->next->size = list->size - (size + sizeof(t_list));
				list->size = size;
			}
			tmp = list->start;
			list = tmp2;
			return (tmp);
		}
		list = list->next;
	}
	return (NULL);
}
