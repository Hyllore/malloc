/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:57:28 by droly             #+#    #+#             */
/*   Updated: 2017/03/29 18:00:24 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*copy_void(void *ptr, void *tmp2, size_t size, size_t old_size)
{
	size_t i;

	i = 0;
	if (size > old_size)
	{
		while (i < old_size)
		{
			((char*)tmp2)[i] = ((unsigned char*)ptr)[i];
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			((char*)tmp2)[i] = ((unsigned char*)ptr)[i];
			i++;
		}
	}
	return (tmp2);
}

void		*realloc(void *ptr, size_t size)
{
	t_list	*tmp;
	void	*tmp2;

	ft_putstr("\nrealloc\n");
	tmp = list;
	ft_putstr("c la --->");
	showadd(ptr);
	if (!ptr)
	{
		ptr = malloc(size);
		list = tmp;
		return (tmp);
	}
	while (list != NULL && list->start != ptr)
	{
		ft_putstr("encore un -->");
//		showadd();
		list = list->next;
	}
	if (list == NULL || size > 2147483606)
	{
		list = tmp;
		ft_putstr("\nrealloc out 2\n");
		return (NULL);
	}
	if (size == 0)
	{
		free(ptr);
		ft_putstr("\nrealloc out 3\n");
		list = tmp;
		return (NULL);
	}
	if (size != list->size)
	{
		list = tmp;
		tmp2 = malloc(size);
		tmp2 = copy_void(ptr, tmp2, size, list->size);
		free(ptr);
		list = tmp;
		ft_putstr("\nrealloc out 4\n");
		return (tmp2);
	}
	list = tmp;
	ft_putstr("\nrealloc out\n");
	return (ptr);
}
