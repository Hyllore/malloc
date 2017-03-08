/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:12:30 by droly             #+#    #+#             */
/*   Updated: 2017/03/08 17:36:58 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_list *list;

t_list		*split_mem(size_t size, t_list *list)
{
	int i;

	i = 0;
	list->size = size;
	list->isfree = 1;
	printf("list %p\n", list->start);
	list->next = &list->start[size + 1];
	list->next->isfree = 0;
	list->next->start = &list->start[size + sizeof(t_list) + 1];
	list->next->next = NULL;
	return (list);
}

void	*add_new(t_list *list, t_list *tmp2, size_t size)
{
	t_list *tmp;
	tmp2 = list;
	printf("\nyo\n");
//	check_free()
	while (list != NULL)
	{
		printf("\nyo2\n");
		if (list->isfree == 0 && list->size >= (size + sizeof(t_list)) && list->next != NULL)
		{
			if (size + sizeof(t_list) + 1 >= list->size)
			{
				list->isfree = 1;
				return (list->start);
			}
			else
			{
				tmp = &list->start[size + 1];
				tmp->isfree = 0;
				tmp->next = list->next;
				tmp->start = &tmp[sizeof(t_list) + 1];
				tmp->size = list->size - (sizeof(t_list) + size);
				list->size = size;
				tmp = &list->start[size + 1];
				list->next = tmp;
			}
		}
		else if (list->isfree == 0 && list->size >= (size + sizeof(t_list)))
		{
				printf("\nyo4\n");
				list->isfree = 1;
				list->next = &list->start[size + 1];
				list->next->isfree = 0;
				list->next->start = &list->start[size + sizeof(t_list) + 1];
				list->next->next = NULL;
				list->next->size = list->size - (size + sizeof(t_list));
				list->size = size;
				list = tmp2;
				printf("list %p\n", list->start);
				printf("\nyo4\n");
				return (list->start);
		}
		list = list->next;
	}
	return (NULL);
}

t_list	*begin_new(t_list *list, int num,  size_t size)
{
	void *tmp;

	tmp = NULL;
	printf("\nhey\n");
	tmp = mmap(0, (num * getpagesize()), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	list = &tmp[0];
	printf("sizet_listjve%lu\n", sizeof(t_list));
	list->start = &tmp[sizeof(t_list) + 1];
	printf("tmp %p\n", &tmp[sizeof(t_list)]);
	list = split_mem(size, list);
	list->next->size = ((num * getpagesize()) - (size + sizeof(t_list)));
	return (list);
}

void	*ft_malloc(size_t size)
{
	void *tmp;
	t_list *tmp2;

	printf("\nsizeof t list  %lu\n", (sizeof(t_list)));
	if (list)
		return (add_new(list, tmp2, size));
	else
	{
		if ((size + sizeof(t_list)) <= (2 * getpagesize()))
		{
			list = begin_new(list, 2, size);
			tmp2 = list;
		}
		if ((size + sizeof(t_list)) <= (16 * getpagesize()) && size >= (2 * getpagesize()))
		{
//			printf("\nhey\n");
//			tmp = mmap(0, (16 * getpagesize()), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
//			list = &tmp[0];
//			tmp2 = list;
//			printf("sizet_listjve%lu\n", sizeof(t_list));
//			list->start = &tmp[sizeof(t_list) + 1];
//			printf("tmp %p\n", &tmp[sizeof(t_list)]);
//			list = split_mem(size, list);
//			list->next->size = ((16 * getpagesize()) - (size + sizeof(t_list)));
			list = begin_new(list, 16, size);
			tmp2 = list;
		}
		else
			return (mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
	}
	list = tmp2;
	return (list->start);
}

int main(void)
{
	char **str;
	int i;

	i = 0;
	printf("\nlu %lu\n", (sizeof(t_list)));
	*str = ft_malloc(sizeof(int) * 8);
	printf("\nlu %lu\n", (sizeof(t_list)));
	printf("ext %p\n", *str);
	*str = ft_malloc(sizeof(int) * 8);
	*str = ft_malloc(sizeof(int) * 25);
	*str = ft_malloc(sizeof(int) * 100);
	*str = ft_malloc(sizeof(int) * 1000);
	while (list != NULL)
	{
		printf("\nadresse %p\n", list);
//		i = 0;
//		while (i++ < 56)
//			printf("\nadresse %p\n", list->start--);
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
