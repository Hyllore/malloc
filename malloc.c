/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:12:30 by droly             #+#    #+#             */
/*   Updated: 2017/05/11 10:39:44 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				check_free(t_list *g_list, size_t size, t_list *tmp2, int page)
{
	while (g_list != NULL)
	{
		if (g_list->isfree == 0 && ((g_list->type == 2 && size <= g_list->size)
					|| g_list->size >= (size + sizeof(t_list) + 1)))
		{
			if ((g_list->type == 0 && size <= ((unsigned long)(8 * page)
			/ 100)) || (g_list->type == 1 && size <= (unsigned long)((32 *
			page) / 100) && size > (unsigned long)((8 *
			page) / 100)) || (g_list->type == 2 && size >
		(unsigned long)((32 * page) / 100)))
			{
				g_list = tmp2;
				return (1);
			}
		}
		g_list = g_list->next;
	}
	g_list = tmp2;
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

t_list			*begin_new(t_list *g_list, int num, size_t size, int type)
{
	void		*tmp;
	static int	i = 0;
	static int	page = -2;

	if (page == -2)
		page = getpagesize();
	tmp = begin_new2(num, NULL, page);
	g_list = tmp;
	g_list->start = &tmp[sizeof(t_list)];
	g_list = split_mem(size, g_list, num);
	g_list->floor = i;
	g_list->type = type;
	if (num <= 32)
	{
		g_list->next->size = (((num * page) + (sizeof(t_list) * 100))
				- (size + sizeof(t_list)));
		g_list->next->floor = i;
		g_list->next->type = type;
	}
	i++;
	return (g_list);
}

void			*tmpfunc(size_t size, int page)
{
	void		*tmp4;
	t_list		*tmp3;
	t_list		*tmp2;

	tmp2 = g_list;
	tmp3 = check_size(NULL, size, page);
	while (g_list->next != NULL)
		g_list = g_list->next;
	if (g_list->next == NULL)
		g_list->next = tmp3;
	g_list = g_list->next;
	tmp4 = g_list->start;
	g_list = tmp2;
	return (tmp4);
}

void			*malloc(size_t size)
{
	t_list		*tmp2;
	void		*tmp4;
	static int	page = -2;

	if (page == -2)
		page = getpagesize();
	if (size > 2147483606 || size <= 0)
		return (NULL);
	if (g_list && check_free(g_list, size, g_list, page) == 0)
		return (tmpfunc(size, page));
	else if (g_list)
		return (add_new(g_list, page, size, g_list));
	else
	{
		g_list = check_size(g_list, size, page);
		tmp2 = g_list;
	}
	tmp4 = g_list->start;
	g_list = tmp2;
	return (tmp4);
}
