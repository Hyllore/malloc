/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:57:28 by droly             #+#    #+#             */
/*   Updated: 2017/05/11 10:36:52 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list		*split_mem(size_t size, t_list *g_list, int num)
{
	int		i;

	i = 0;
	g_list->size = size;
	g_list->isfree = 1;
	if (num <= 32)
	{
		g_list->next = &g_list->start[size];
		g_list->next->isfree = 0;
		g_list->next->start = &g_list->start[size + sizeof(t_list)];
		g_list->next->next = NULL;
	}
	return (g_list);
}

void		*add_new2(t_list *g_list, size_t size, t_list *tmp, t_list *tmp2)
{
	void	*tmp3;

	g_list->isfree = 1;
	if (g_list->size >= (sizeof(t_list) + size + 1))
	{
		tmp = &(g_list->start[size]);
		tmp->start = &(g_list->start[size + sizeof(t_list)]);
		tmp->floor = g_list->floor;
		tmp->type = g_list->type;
		tmp->next = g_list->next;
		tmp->isfree = 0;
		tmp->size = g_list->size - (sizeof(t_list) + size);
		g_list->next = tmp;
		g_list->size = size;
	}
	tmp3 = g_list->start;
	g_list = tmp2;
	return (tmp3);
}

void		*calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0 || size > 2147483606)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void		*realloc2(void *ptr, size_t size, size_t tmpi, t_list *tmp)
{
	void *tmp2;

	tmpi = g_list->size;
	g_list = tmp;
	if ((tmp2 = malloc(size)) == NULL)
		return (NULL);
	tmp2 = ft_memcpy(tmp2, ptr, size > tmpi ? tmpi : size);
	free(ptr);
	return (tmp2);
}

void		*realloc(void *ptr, size_t size)
{
	t_list	*tmp;

	if (!ptr)
	{
		ptr = malloc(size);
		return (ptr);
	}
	tmp = g_list;
	while (g_list != NULL && g_list->start != ptr)
		g_list = g_list->next;
	if (g_list == NULL || size > 2147483606 || size == 0)
	{
		g_list = tmp;
		if (size == 0)
			free(ptr);
		return (NULL);
	}
	if (size != g_list->size)
		return (realloc2(ptr, size, 0, tmp));
	g_list = tmp;
	return (ptr);
}
