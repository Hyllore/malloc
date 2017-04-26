/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:57:28 by droly             #+#    #+#             */
/*   Updated: 2017/04/26 14:14:49 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*calloc(size_t count, size_t size)
{
	void *ptr;

	ft_putstr("|calloc|");
	if (count == 0 || size == 0)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
	void	*tmp;
	void	*tmp2;

	ft_putstr("|realloc|");
	if (!ptr)
	{
		ptr = malloc(size);
		return (ptr);
	}
	tmp = list;
	while (list != NULL && list->start != ptr)
		list = list->next;
	if (list == NULL || size > 2147483606 || size == 0)
	{
		list = tmp;
		if (size == 0)
			free(ptr);
		return (NULL);
	}
	if (size != list->size)
	{
		ft_putstr("|found realloc|");
		list = tmp;
		if ((tmp2 = malloc(size)) == NULL)
			return (NULL);
		tmp2 = ft_memcpy(tmp2, ptr, size > list->size ? list->size : size);
		free(ptr);
		return (tmp2);
	}
	list = tmp;
	return (ptr);
}
