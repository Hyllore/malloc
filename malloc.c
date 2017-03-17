/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:12:30 by droly             #+#    #+#             */
/*   Updated: 2017/03/17 11:44:31 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		check_free(t_list *list, size_t size, t_list *tmp2)
{
	while (list != NULL)
	{
		if (list->isfree == 0 && list->size >= (size + sizeof(t_list)))
		{
			if ((list->type == 0 && size <= ((unsigned long)(4 * getpagesize()) / 100)) || (list->type == 1 && size <= (unsigned long)((16 * getpagesize()) / 100) && size > (unsigned long)((4 * getpagesize()) / 100)))
			{
				list = tmp2;
				return (1);
			}
		}
		list = list->next;
	}
	list = tmp2;
	return (0);
}

t_list	*begin_new(t_list *list, int num,  size_t size, int type)
{
	void *tmp;
	static int i = 0;

	tmp = NULL;
	if((int)(tmp = mmap(0, ((num * getpagesize()) + (sizeof(t_list) * 100)), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == -1)
		return (NULL);
	list = &tmp[0];
	list->start = &tmp[sizeof(t_list)];
	list = split_mem(size, list, num);
	list->floor = i;
	list->type = type;
	if (num <= 16)
	{
		list->next->size = (((num * getpagesize()) + (sizeof(t_list) * 100)) - (size + sizeof(t_list)));
		list->next->floor = i;
		list->next->type = type;
	}
	i++;
	return (list);
}

t_list	*check_size(t_list *list, size_t size)
{
//	printf("\njte");
	if (size <= (unsigned long)((4 * getpagesize()) / 100))
	{
//		printf("1er if 2 : %lu\n", size);
		list = begin_new(list, 4, size, 0);
	}
	if (size <= (unsigned long)((16 * getpagesize()) / 100) && size > (unsigned long)((4 * getpagesize()) / 100))
	{
//		printf("2eme if 2 : %lu\n", size);
		list = begin_new(list, 16, size, 1);
	}
	if (size > (unsigned long)((16 * getpagesize()) / 100))
	{
//		printf("3eme if 2 : %lu\n", size);
		list = begin_new(list, size + sizeof(t_list) + 1, size, 2);
	}
//	printf(" bez\n");
	return (list);
}

void	*ft_malloc(size_t size)
{
	t_list *tmp2;
	t_list *tmp3;
	void *tmp4;

	if (list && check_free(list, size, NULL) == 0)
	{
//		printf("1er if : %lu\n", size);
		tmp3 = list;
		tmp2 = check_size(NULL, size);
		while (list->next != NULL)
			list = list->next;
		if (list->next == NULL)
			list->next = tmp2;
		tmp2 = tmp3;
	}
	else if (list)
	{
//		printf("2eme if : %lu\n", size);
		return (add_new(list, NULL, size));
	}
	else
	{
//		printf("3eme if : %lu\n", size);
		list = check_size(list, size);
		tmp2 = list;
	}
	if (list == NULL)
		return (NULL);
	tmp4 = list->start;
	list = tmp2;
	return (tmp4);
}

int main(void)
{
	int *str;
	int *ptr;
	int i;
	t_list *tmp;

	i = 0;
	printf("\nlu %lu\n", (sizeof(t_list)));
//	if ((*str = ft_malloc(sizeof(int) * 8)) == NULL)
//		printf("\nnull\n");
	printf("\nlu %lu\n", (sizeof(t_list)));
//	printf("ext %p\n", *str);
//segfault si trop gros chiffre
//	str = ft_malloc(sizeof(int) * 8);
///	str = ft_malloc(sizeof(int) * 25);
//	str = ft_malloc(sizeof(int) * 100);
//	str = ft_malloc(sizeof(int) * 1000);
//	str = ft_malloc(sizeof(int) * 10000);
//	str = ft_malloc(sizeof(int) * 20000);
//	str = ft_malloc(sizeof(int) * 1000000);
//	str = ft_malloc(sizeof(int) * 20000);
//	str = ft_malloc(sizeof(int) * 10000);
//	str = ft_malloc(sizeof(int) * 1000);
//	str = ft_malloc(sizeof(int) * 100);
//	str = ft_malloc(sizeof(int) * 2);
	int y;

	y = 0;
//	while (i < 3)
//	{
		printf("\nnb : %d\n", i);
		str = ft_malloc(5);
		printf("\nadresse str %p\n", str);
		printf("\nnb : %d\n", i);
		ptr = ft_malloc(5);
		printf("\nadresse ptr %p\n", ptr);
//		ft_free(str);
//	y = 0;
///		while (y < 20)
//		{
//			str[y] = 1;
///			printf("\nchiffre : %d\n", str[y]);
//			y++;
//		}
//		i++;
//	}
	tmp = list;
	i = 0;
//	while (i < 69536)
//	{
//		list->start++;
//		i++;
//	}
//		printf("\nadresses fin %p\n", list->start++);
	i = 0;
	//trouver pourquoi segfault si 655 et si plus de 100 appel
	ft_free(ptr);
	list = tmp;
	while (list != NULL)
	{
		printf("\nadresse %p\n", list);
//		i = 0;
//		while (i++ < 56)
//			printf("\nadresse %p\n", list->start--);
		printf("\nlist sortie %p\n", list->start);
		printf("\nlist free %d\n", list->isfree);
		i++;
//		while (i < 32)
//		{
//			printf(" %p\n", list->start++);
//			i++;
//		}
		printf("type %d\n", list->type);
		printf("floor %d\n", list->floor);
		printf("size %lu\n", list->size);
		if (list->next != NULL)
			list = list->next;
		else
			break;
	}
	i = 0;
//	while (i < 36)
//	{
//		printf("\nadresses dispos %p\n", list->start++);
//		i++;
//	}
	printf("\nnobre de tours : %d\n", i);
	printf("\nsize get page 16 / 100 : %d\n", 16 * getpagesize() / 100);
	printf("\nsize get page 4 / 100  : %d\n", 4 * getpagesize()/ 100);
	printf("\nsize get page 16  : %d\n", 16 * getpagesize());
	printf("\nsize get page 4  : %d\n", 4 * getpagesize());
	printf("\nsize get page 16 + sizeof(t_list) * 100 : %lu\n", 16 * getpagesize() +sizeof(t_list) * 100 );
	printf("\nsize get page 4 + sizeof(t_list) * 100  : %lu\n", 4 * getpagesize() +sizeof(t_list) * 100 );
//	str = malloc(sizeof(int) * 2);
//	str[0] = 544;
//	str[1] = 5454;
//	str[2] = 64584;
//	printf("%d%d%d", str[0], str[1], str[2]);
//	str = malloc(8);
//	free(str);
	list = tmp;
	//trouver pourquoi c tjr la premiere adresse qui free
}


//			printf("\nhey\n");
//			tmp = mmap(0, (16 * getpagesize()), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
//			list = &tmp[0];
//			tmp2 = list;
//			printf("sizet_listjve%lu\n", sizeof(t_list));
//			list->start = &tmp[sizeof(t_list) + 1];
//			printf("tmp %p\n", &tmp[sizeof(t_list)]);
//			list = split_mem(size, list);
//			list->next->size = ((16 * getpagesize()) - (size + sizeof(t_list)));

