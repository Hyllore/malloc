/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:57:28 by droly             #+#    #+#             */
/*   Updated: 2017/04/21 09:59:26 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*calloc(size_t count, size_t size)
{
	void *ptr;

//		ft_putstr("\ncalloc enter\n");
	if (count == 0 || size == 0)
	{
//		ft_putstr("\ncalloc out 2\n");
		return (NULL);
	}
	ptr = malloc(count * size);
	if (ptr == NULL)
	{
//		ft_putstr("\ncalloc out 3\n");
		return (NULL);
	}
	ft_bzero(ptr, count * size);
//	ft_putstr("\ncalloc out 4\n");
	return (ptr);
}

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

//	ft_putstr("\nrealloc\n");
	tmp = list;
//	ft_putstr("c la --->");
//	showadd(ptr);
	if (!ptr)
	{
//		ft_putstr("\nrealloc out 5\n");
		ptr = malloc(size);
		list = tmp;
		return (ptr);
	}
	while (list != NULL && list->start != ptr)
	{
//		ft_putstr("encore un -->");
//		showadd();
		list = list->next;
	}
	if (list == NULL || size > 2147483606)
	{
		list = tmp;
//		ft_putstr("\nrealloc out 2\n");
		return (NULL);
	}
	if (size == 0)
	{
		list = tmp;
		free(ptr);
//		ft_putstr("\nrealloc out 3\n");
//	list = tmp;
		return (NULL);
	}
	if (size != list->size)
	{
		list = tmp;
		tmp2 = malloc(size);
		tmp2 = copy_void(ptr, tmp2, size, list->size);
		free(ptr);
//		list = tmp;
//		ft_putstr("\nrealloc out 4\n");
		return (tmp2);
	}
	list = tmp;
//	ft_putstr("\nrealloc out\n");
	return (ptr);
}
