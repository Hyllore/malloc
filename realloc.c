/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:57:28 by droly             #+#    #+#             */
/*   Updated: 2017/04/24 15:37:27 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*calloc(size_t count, size_t size)
{
	void *ptr;

	if (count == 0 || size == 0)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
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
	void	*tmp;
	void	*tmp2;

	tmp = NULL;
	if (!ptr)
	{
		ptr = malloc(size);
		return (ptr);
	}
	while (list != NULL && list->start != ptr)
		list = list->next;
	if (list == NULL || size > 2147483606)
	{
		list = tmp;
		return (NULL);
	}
	if (size == 0)
	{
		list = tmp;
		free(ptr);
		return (NULL);
	}
	if (size != list->size)
	{
		list = tmp;
		tmp2 = malloc(size);
		tmp2 = copy_void(ptr, tmp2, size, list->size);
		free(ptr);
		return (tmp2);
	}
	list = tmp;
	return (ptr);
}
