/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:46:32 by droly             #+#    #+#             */
/*   Updated: 2017/04/21 10:01:31 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list		*split_mem(size_t size, t_list *list, int num)
{
	int		i;

	i = 0;
//	ft_putstr("\nmalloc split_mem\n");
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
//	ft_putstr("\nmalloc add_new2`\n");
	list->isfree = 1;
/*	ft_putchar('a');
	ft_putnbr(size);

		ft_putstr("\nT: list->type:");
			ft_putnbr(list->type);
		ft_putstr("\nT: list->floor:");
			ft_putnbr(list->floor);
		ft_putstr("\nT: list->isfree:");
			ft_putnbr(list->isfree);
		ft_putstr("\nT: list->size:");
			ft_putnbr(list->size);
		ft_putchar('\n');*/

	if (list->size >= (sizeof(t_list) + size + 1))
	{
//		ft_putchar('b');
		tmp = &(list->start[size]);
//		list->start = "pipi";
//		ft_putstr("\nlist->next->type:");
//		ft_putnbr(list->next->type);
//		if (!tmp)
//			ft_putstr("\nniquetamer\n");
//		ft_putchar('n');
//		if (&tmp[sizeof(t_list)] == NULL)
//			ft_putstr("hello\n");
//		ft_putchar('y');
		tmp->start = &(list->start[size + sizeof(t_list)]);
//		ft_putchar('f');
		tmp->floor = list->floor;
//		ft_putchar('g');
		tmp->type = list->type;
//		ft_putchar('h');
//		ft_putchar('d');
		tmp->next = list->next;
//		ft_putchar('e');
		tmp->isfree = 0;
//		ft_putchar('c');
		tmp->size = list->size - (sizeof(t_list) + size);
//		ft_putchar('i');
//		tmp = &list->start[size];
		list->next = tmp;
//		ft_putchar('j');
		list->size = size;
//		ft_putchar('k');
	}
//		ft_putstr("\nmalloc add_new2`fklsrjknv\n");
//	if (size >= list->size)
//	{
//		tmp = 0;
//	}
//	ft_putnbr(size);
/*	ft_putstr("\nmalloc add_new2 fin\n");
//	ft_putnbr(list->size);
	ft_putstr("\nmalloc add_new2 fin 2\n");
		ft_putstr("\nlist->type:");
			ft_putnbr(list->type);
		ft_putstr("\nlist->floor:");
			ft_putnbr(list->floor);
		ft_putstr("\nlist->isfree:");
			ft_putnbr(list->isfree);
		ft_putstr("\nlist->size:");
			ft_putnbr(list->size);
		ft_putchar('\n');
	ft_putstr("\nmalloc add_new2 fin 2\n");
		ft_putstr("\nlist->next->type:");
			ft_putnbr(list->next->type);
		ft_putstr("\nlist->next->floor:");
			ft_putnbr(list->next->floor);
		ft_putstr("\nlist->next->isfree:");
			ft_putnbr(list->next->isfree);
		ft_putstr("\nlist->next->size:");
			ft_putnbr(list->next->size);
		ft_putchar('\n');
		ft_putstr("\ntmp2->type:");
			ft_putnbr(tmp2->type);
		ft_putstr("\ntmp2->floor:");
			ft_putnbr(tmp2->floor);
		ft_putstr("\ntmp2->isfree:");
			ft_putnbr(tmp2->isfree);
		ft_putstr("\ntmp2->size:");
			ft_putnbr(tmp2->size);
		ft_putchar('\n');*/
	tmp3 = list->start;
	tmp2 = list;
	return (tmp3);
}

//voir modifs, j'ai modifsdif truc dans add_new2 et segfault dans add new3 mtn , j'ai add tmp2 = list dasn addnew

void		add_new3(t_list *list, size_t size)
{
//	ft_putnbr(list->size);

//	ft_putstr("\nmalloc add_new3\n");
//	ft_itoa_base_ull(size, 10);
	list->next = &list->start[size];
//	ft_putstr("\nmalloc add_new3 fin 2\n");
	list->next->isfree = 0;
//	ft_putstr("\nmalloc add_new3 fin 3\n");
	list->next->floor = list->floor;
//	ft_putstr("\nmalloc add_new3 fin 4\n");
	list->next->type = list->type;
//	ft_putstr("\nmalloc add_new3 fin 5\n");
	list->next->start = &list->start[size + sizeof(t_list)];
//	ft_putstr("\nmalloc add_new3 fin 6\n");
	list->next->next = NULL;
//	ft_putstr("\nmalloc add_new3 fin 7\n");
	list->next->size = list->size - (size + sizeof(t_list));
//	ft_putstr("\nmalloc add_new3 fin 8\n");
	list->size = size;
//	ft_putstr("\nmalloc add_new3 fin 9\n");
}

void		*add_new(t_list *list, t_list *tmp2, size_t size, void *tmp)
{
//	ft_putstr("\nmalloc add_new\n");

	tmp2 = list;
	while (list != NULL)
	{
//		ft_putstr("\nlist->type:");
//			ft_putnbr(list->type);
//		ft_putstr("\nlist->floor:");
/*			ft_putnbr(list->floor);
		ft_putstr("\nlist->isfree:");
			ft_putnbr(list->isfree);
		ft_putstr("\nlist->size:");
			ft_putnbr(list->size);
		ft_putchar('\n');*/
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
//			if (list->size >= (sizeof(t_list) + size + 1))
			add_new3(list, size);
			tmp = list->start;
			list = tmp2;
//	ft_putstr("\nmalloc add_new3 fin\n");
			return (tmp);
		}
		list = list->next;
	}
	list = tmp2;
	return (NULL);
}
