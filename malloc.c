/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:12:30 by droly             #+#    #+#             */
/*   Updated: 2017/03/06 17:44:58 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list *list;

int			count_size_remaining(t_list *list)
{
	int size_remaining;

	size_remaining = 0;
	while (list->next != NULL)
	{
		size_remaining = list->size + sizeof(t_list);
	}
	return(size_remaining);
}

t_list		*split_mem(size_t size, t_list *list)
{
	int i;

	i = 0;
//	printf("\nsizeof t list  %lu\n", (sizeof(t_list)));
//	list = &ptr[0];
//	struc->list = &struc->ptr[sizeof(t_struct) + 1];
	list->size = size;
	list->isfree = 1;
	printf("list %p\n", list->start);
//	printf("%d\n", (int)list->isfree);
//	printf("%lu\n", sizeof(t_list));
	list->next = &list->start[size];
	list->next->isfree = 0;
	list->next->start = &list->start[size + sizeof(t_list)];
	list->next->next = NULL;
//	count_size_remaining(list);
	return (list);
}

void	*ft_malloc(size_t size)
{
	void *tmp;
	t_list *tmp2;

	tmp2 = list;
	printf("\nsizeof t list  %lu\n", (sizeof(t_list)));
	if (list)
	{
		printf("\nyo\n");
//		tmp2 = list;
		while (list != NULL)
		{
		printf("\nyo2\n");
			if (list->isfree == 0)
			{
				printf("\nyo3\n");
				if (list->size >= (size + sizeof(t_list)))
				{
					printf("\nyo4\n");
					list->isfree = 1;
					list->next = &list->start[size];
					list->next->isfree = 0;
					list->next->start = &list->start[size + sizeof(t_list)];
					list->next->next = NULL;
					list->next->size = list->size - (size + sizeof(t_list));
					list->size = size;
					list = tmp2;
					return (list->start);
				}
			}
			list = list->next;
		}
		return (NULL);
	}
	printf("\nlu %lu\n", (sizeof(t_list)));
	if (!list)
	{
		if ((size + sizeof(t_list)) <= (2 * getpagesize()))
		{
			printf("\nhey\n");
			tmp = mmap(0, (2 * getpagesize()), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
			list = &tmp[0];
			tmp2 = list;
			list->start = &tmp[sizeof(t_list)];
			printf("tmp %p\n", &tmp[sizeof(t_list)]);
			list = split_mem(size, list);
			list->next->size = ((2 * getpagesize()) - (size + sizeof(t_list)));
		}
		if ((size + sizeof(t_list)) <= (16 * getpagesize()) && size >= (2 * getpagesize()))
		{
			tmp = mmap(0, (16 * getpagesize()), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
			list = &tmp[0];
			list->start = &tmp[sizeof(t_list)];
			list = split_mem(size, list);
			list->next->size = ((16 * getpagesize()) - (size + sizeof(t_list)));
		}
		else
			tmp = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	}
//	list = tmp2;
	return (list->start);
}

int main(void)
{
	char **str;
	int i;

	i = 0;
	printf("\nlu %lu\n", (sizeof(t_list)));
	*str = ft_malloc(sizeof(int) * 8);
	printf("ext %p\n", *str);
	*str = ft_malloc(sizeof(int) * 8);
	*str = ft_malloc(sizeof(int) * 25);
	*str = ft_malloc(sizeof(int) * 100);
	while (list != NULL)
	{
		printf("\nlist sortie %p\n", list->start);
		i= 0;
/*		while (i < 32)
		{
			printf(" %p\n", list->start++);
			i++;
		}*/
		printf("size %d\n", list->size);
		list = list->next;
	}
		printf("\nsize get page %d\n", 2 * getpagesize());

}
