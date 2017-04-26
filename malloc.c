

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:12:30 by droly             #+#    #+#             */
/*   Updated: 2017/04/24 16:09:41 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_free(t_list *list, size_t size, t_list *tmp2, int page)
{
	while (list != NULL)
	{
		if (list->isfree == 0 && ((list->type == 2 && size <= list->size) || list->size >= (size + sizeof(t_list) + 1)))
		{
			if ((list->type == 0 && size <= ((unsigned long)(4 * page)
			/ 100)) || (list->type == 1 && size <= (unsigned long)((16 *
			page) / 100) && size > (unsigned long)((4 *
			page) / 100)) || (list->type == 2 && size > (unsigned long)((16 * page) / 100)))
			{
//				ft_putstr("\nwallah\n");
				list = tmp2;
//				ft_putstr("\nwallah2\n");
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
	ft_putstr("|mmap :");
	ft_putnbr(num);
	ft_putchar('|');
	if (num <= 16)
	{
		if ((tmp = mmap(0, ((num * page) + (sizeof(t_list) *
		100)), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) ==
				MAP_FAILED)
			return (NULL);
	}
	else
	{
//		ft_putstr("\nmmap\n");
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
	static int page = -2;

	if (page == -2)
		page = getpagesize();
	tmp = begin_new2(num, NULL, page);
	list = tmp;
	list->start = &tmp[sizeof(t_list)];
	list = split_mem(size, list, num);
	list->floor = i;
	list->type = type;
	if (num <= 16)
	{
		list->next->size = (((num * page) + (sizeof(t_list) * 100))
				- (size + sizeof(t_list)));
		list->next->floor = i;
		list->next->type = type;
	}
	i++;
	return (list);
}

t_list			*check_size(t_list *list, size_t size, int page)
{
	if (size <= (unsigned long)((4 * page) / 100))
		list = begin_new(list, 4, size, 0);
	if (size <= (unsigned long)((16 * page) / 100) && size >
			(unsigned long)((4 * page) / 100))
		list = begin_new(list, 16, size, 1);
	if (size > (unsigned long)((16 * page) / 100))
		list = begin_new(list, size + sizeof(t_list), size, 2);
	return (list);
}

void			*malloc(size_t size)
{
	t_list		*tmp2;
	t_list		*tmp3;
	void		*tmp4;
	static int page = -2;

	ft_putstr("|malloc|");
	if (page == -2)
		page = getpagesize();
	if (size > 2147483606)
		return (NULL);
	if (list && check_free(list, size, list, page) == 0)
	{
		ft_putstr("\n|new-mmap|\n");
		tmp3 = list;
		tmp2 = check_size(NULL, size, page);
		while (list->next != NULL)
			list = list->next;
		if (list->next == NULL)
			list->next = tmp2;
		list = list->next;
//		ft_putstr("\nfloor : ");
//		ft_putnbr(list->floor);
	}
	else if (list)
		return (add_new(list, page, size, list));
	else
	{
		ft_putstr("|New-begining|");
		list = check_size(list, size, page);
		tmp2 = list;
	}
	tmp4 = list->start;
	list = tmp2;
	return (tmp4);
}
