/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:46:32 by droly             #+#    #+#             */
/*   Updated: 2017/03/30 18:14:27 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list		*split_mem(size_t size, t_list *list, int num)
{
	int		i;

	i = 0;
	ft_putstr("\nmalloc split_mem\n");
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
	ft_putstr("\nmalloc add_new2`\n");
	list->isfree = 1;
//	if (list->size >= (sizeof(t_list) + size + 1))
//	{
//		tmp = &list->start[size];
//		tmp->isfree = 0;
//		tmp->next = list->next;
//		tmp->start = &tmp[sizeof(t_list)];
//		tmp->floor = list->floor;
//		tmp->type = list->type;
//		tmp->size = list->size - (sizeof(t_list) + size);
//		tmp = &list->start[size];
//		list->next = tmp;
//		list->size = size;
//	}
		ft_putstr("\nmalloc add_new2`fklsrjknv\n");
	if (size >= list->size)
	{
		tmp = 0;
	}
	ft_putnbr(size);
	ft_putstr("\nmalloc add_new2 fin\n");
	ft_putnbr(list->size);
	ft_putstr("\nmalloc add_new2 fin 2\n");
	list = tmp2;
	return (list->start);
}

//voir modifs, j'ai modifsdif truc dans add_new2 et segfault dans add new3 mtn , j'ai add tmp2 = list dasn addnew

void		add_new3(t_list *list, size_t size)
{
	ft_putstr("\nmalloc add_new3\n");
	list->next = &list->start[size];
	list->next->isfree = 0;
	list->next->floor = list->floor;
	list->next->type = list->type;
	list->next->start = &list->start[size + sizeof(t_list)];
	list->next->next = NULL;
	list->next->size = list->size - (size + sizeof(t_list));
	list->size = size;
}

void		*add_new(t_list *list, t_list *tmp2, size_t size, void *tmp)
{
	ft_putstr("\nmalloc add_new\n");

	tmp2 = list;
	while (list != NULL)
	{
		if (list->isfree == 0 && list->size >= size && list->next != NULL &&
		(((list->type == 0 && size <= ((unsigned long)(4 * getpagesize()) /
		100)) || (list->type == 1 && size <= ((unsigned long)(16 *
		getpagesize()) / 100) && size > ((unsigned long)(4 * getpagesize()) /
		100)))))
			return (add_new2(list, size, NULL, tmp2));
		else if (list->isfree == 0 && list->size >= size && (((list->type == 0
		&& size <= ((unsigned long)(4 * getpagesize()) / 100)) || (list->type
		== 1 && size <= ((unsigned long)(16 * getpagesize()) / 100) && size >
		((unsigned long)(4 * getpagesize()) / 100)))))
		{
			list->isfree = 1;
			if (list->size >= (sizeof(t_list) + size + 1))
				add_new3(list, size);
			tmp = list->start;
			list = tmp2;
	ft_putstr("\nmalloc add_new3 fin\n");
			return (tmp);
		}
		list = list->next;
	}
	list = tmp2;
	return (NULL);
}
