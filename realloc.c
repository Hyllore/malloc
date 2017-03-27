/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:57:28 by droly             #+#    #+#             */
/*   Updated: 2017/03/27 14:23:05 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//finir realloc avec le coup des size la bonne copie et comprendre comment ca marche quand size < old_size

void		*copy_void(void *ptr, void *tmp2, size_t size, size_t old_size)
{
	size_t i;

	i = 0;
	if (size > old_size)
	{
		while (i < old_size)
		{
//			printf("connard4");
			((char*)tmp2)[i] = ((unsigned char*)ptr)[i];
			i++;
		}
	}
	else
	{
		while (i < size)
		{
//			printf("connard5");
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

	tmp = list;
	while (list != NULL && list->start != ptr)
		list = list->next;
	if (list == NULL)
	{
//		printf("connard1");
		list = tmp;
		return (NULL);
	}
	if (size == 0)
	{
//		printf("connard2");
		free(ptr);
		list = tmp;
		return (NULL);
	}
	if (size != list->size)
	{
//		printf("\nconnard3\n");
//		printf("\nsize : %lu\n", list->size);
		list = tmp;
		tmp2 = malloc(size);
		tmp2 = copy_void(ptr, tmp2, size, list->size);
		free(ptr);
//		printf("\nsizetamer : %p\n", list);
		list = tmp;
//		printf("\ntest seg\n");
		return (tmp2);
	}
	list = tmp;
	return (ptr);
}
