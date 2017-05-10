/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:12:30 by droly             #+#    #+#             */
/*   Updated: 2017/05/10 16:29:22 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_free(t_list *list, size_t size, t_list *tmp2, int page)
{
	while (list != NULL)
	{
		if (list->isfree == 0 && ((list->type == 2 && size <= list->size) ||
					list->size >= (size + sizeof(t_list) + 1)))
		{
			if ((list->type == 0 && size <= ((unsigned long)(8 * page)
			/ 100)) || (list->type == 1 && size <= (unsigned long)((32 *
			page) / 100) && size > (unsigned long)((8 *
			page) / 100)) || (list->type == 2 && size >
		(unsigned long)((32 * page) / 100)))
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

void			*begin_new2(int num, t_list *tmp, int page)
{
	if (num <= 32)
	{
		if ((tmp = mmap(0, ((num * page) + (sizeof(t_list) *
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
	static int	page = -2;

	if (page == -2)
		page = getpagesize();
	tmp = begin_new2(num, NULL, page);
	list = tmp;
	list->start = &tmp[sizeof(t_list)];
	list = split_mem(size, list, num);
	list->floor = i;
	list->type = type;
	if (num <= 32)
	{
		list->next->size = (((num * page) + (sizeof(t_list) * 100))
				- (size + sizeof(t_list)));
		list->next->floor = i;
		list->next->type = type;
	}
	i++;
	return (list);
}

void			*tmpfunc(size_t size, int page)
{
	void		*tmp4;
	t_list		*tmp3;
	t_list		*tmp2;

	tmp2 = list;
	tmp3 = check_size(NULL, size, page);
	while (list->next != NULL)
		list = list->next;
	if (list->next == NULL)
		list->next = tmp3;
	list = list->next;
	tmp4 = list->start;
	list = tmp2;
	return (tmp4);
}

void			*malloc(size_t size)
{
	t_list		*tmp2;
	void		*tmp4;
	static int	page = -2;

//	ft_putnbr(size);
//	ft_putchar(':');
	if (page == -2)
		page = getpagesize();
	if (size > 2147483606 || size <= 0)
		return (NULL);
	if (list && check_free(list, size, list, page) == 0)
		return (tmpfunc(size, page));
	else if (list)
		return (add_new(list, page, size, list));
	else
	{
		list = check_size(list, size, page);
		tmp2 = list;
	}
	tmp4 = list->start;
	list = tmp2;
	return (tmp4);
}
