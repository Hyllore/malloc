/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:12:30 by droly             #+#    #+#             */
/*   Updated: 2017/03/29 18:02:19 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_free(t_list *list, size_t size, t_list *tmp2)
{
	while (list != NULL)
	{
		if (list->isfree == 0 && list->size >= size)
		{
			if ((list->type == 0 && size <= ((unsigned long)(4 * getpagesize())
			/ 100)) || (list->type == 1 && size <= (unsigned long)((16 *
			getpagesize()) / 100) && size > (unsigned long)((4 *
			getpagesize()) / 100)))
			{
				list = tmp2;
				return (1);
			}
		}
		list = list->next;
	}
	list = tmp2;
	return (0);
}

void			*begin_new2(int num, t_list *tmp)
{
	if (num <= 16)
	{
		if ((tmp = mmap(0, ((num * getpagesize()) + (sizeof(t_list) *
		100)), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) ==
				MAP_FAILED)
			return (NULL);
	}
	else
	{
		if ((tmp = mmap(0, num, PROT_READ | PROT_WRITE, MAP_ANON |
						MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			return (NULL);
	}
	return (tmp);
}

t_list			*begin_new(t_list *list, int num, size_t size, int type)
{
	void		*tmp;
	static int	i = 0;

	tmp = begin_new2(num, NULL);
	list = tmp;
	list->start = &tmp[sizeof(t_list)];
	list = split_mem(size, list, num);
	list->floor = i;
	list->type = type;
	if (num <= 16)
	{
		list->next->size = (((num * getpagesize()) + (sizeof(t_list) * 100))
				- (size + sizeof(t_list)));
		list->next->floor = i;
		list->next->type = type;
	}
	i++;
	return (list);
}

t_list			*check_size(t_list *list, size_t size)
{
	if (size <= (unsigned long)((4 * getpagesize()) / 100))
	{
		list = begin_new(list, 4, size, 0);
	}
	if (size <= (unsigned long)((16 * getpagesize()) / 100) && size >
			(unsigned long)((4 * getpagesize()) / 100))
	{
		list = begin_new(list, 16, size, 1);
	}
	if (size > (unsigned long)((16 * getpagesize()) / 100))
	{
		list = begin_new(list, size + sizeof(t_list) + 1, size, 2);
	}
	return (list);
}

void			*malloc(size_t size)
{
	t_list		*tmp2;
	t_list		*tmp3;
	void		*tmp4;

//	write(1, "elo", 3);
//	puts((size + sizeof(t_list)));
//	printf("%u", size + sizeof(t_list));
	ft_putstr("\nmalloc\n");
	if (size > 2147483606)
	{
		ft_putstr("\nmalloc out 2\n");
		return (NULL);
	}
	if (list && check_free(list, size, NULL) == 0)
	{
		ft_putstr("\nmalloc begin new\n");
//		write(1, "elo3", 4);
//		printf("1er if : %lu\n", size);
		tmp3 = list;
		tmp2 = check_size(NULL, size);
		while (list->next != NULL)
			list = list->next;
		if (list->next == NULL)
			list->next = tmp2;
		list = list->next;
		tmp2 = tmp3;
	}
	else if (list)
	{
//		write(1, "elo2", 4);
//		printf("2eme if : %lu\n", size);
		ft_putstr("\nmalloc out 3\n");
		return (add_new(list, NULL, size, list));
	}
	else
	{
		ft_putstr("\nmalloc start\n");
//		write(1, "elo5", 4);
//		printf("3eme if : %lu\n", size);
		list = check_size(list, size);
		tmp2 = list;
	}
//	if (list == NULL)
//		return (NULL);
	tmp4 = list->start;
	list = tmp2;
//	ft_putstr("hey\n");
	ft_putstr("\nmalloc out\n");
//	show_alloc_mem();
	return (tmp4);
}
