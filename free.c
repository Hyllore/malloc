/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/03/22 18:00:23 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			find_start(int floor, t_list *tmp2)
{
	t_list	*tmp3;

	list = tmp2;
	if (tmp2->floor == floor)
	{
		while (list != NULL && list->floor == floor)
			list = list->next;
		return (1);
	}
	while (list != NULL && list->next->floor != floor)
		list = list->next;
	tmp3 = list->next;
	while (tmp3 != NULL && tmp3->floor == floor)
	{
		tmp3 = tmp3->next;
	}
	list->next = tmp3;
	list = tmp2;
	return (0);
}

int			check_unmap(t_list *tmp3)
{
	int		check;
	int		floor;
	int		i;
	int		i2;
	void	*tmp;
	t_list	*tmp2;

	i2 = 0;
	tmp2 = list;
	tmp = NULL;
	i = 0;
	check = 0;
	while (list != NULL)
	{
		printf("\nniktamer\n");
		floor = list->floor;
		tmp = list;
		while (list->next != NULL && floor == list->floor)
		{
			if (list->isfree == 1)
			{
				printf("\nserieux\n");
				check = 1;
				while (list->next != NULL && list->floor == floor)
					list = list->next;
			}
			if (check == 0)
				list = list->next;
			i++;
		}
		if (list->isfree == 1 && list->floor == floor)
			check = 1;
		if (check == 0 && list->type == 0 && i >= 10)
		{
			printf("\nserieux2\n");
			tmp3 = list;
			i2 = find_start(list->floor, tmp2);
			munmap(tmp, ((4 * getpagesize()) + (sizeof(t_list) * 100)));
			if (tmp2 && i2 == 0)
				list = tmp2;
			printf("\ns?\n");
			return (i2);
		}
		if (check == 0 && list->type == 1 && i >= 10)
		{
			printf("\nserieux3\n");
			tmp3 = list;
			find_start(list->floor, tmp2);
			munmap(tmp, ((16 * getpagesize()) + (sizeof(t_list) * 100)));
			if (tmp2 && i2 == 0)
				list = tmp2;
			return (i2);
		}
		check = 0;
		if (i == 0)
			list = list->next;
		i = 0;
	}
	printf("test de merde%d", tmp2->isfree);
	list = tmp2;
	return (0);
}

void		ft_free(void *ptr)
{
	t_list	*tmp2;
	t_list	*tmp3;
	int		i;

	i = 0;
	tmp3 = NULL;
	if (list && ptr)
	{
		tmp2 = list;
		while (list != NULL)
		{
			printf("\nadresses dispos %p\n", list->start);
			printf("\nadresses de tamer la put %p\n", ptr);
			if (list->start == ptr)
			{
				printf("\nslt c 1 test\n");
				list->isfree = 0;
				if (list->type == 2)
				{
					printf("\nserieux4\n");
					tmp3 = list;
					find_start(list->floor, tmp2);
					munmap(tmp3, list->size + sizeof(t_list) + 1);
				}
				else
				{
					list = tmp2;
					i = check_unmap(tmp3);
				}
				if (i == 0)
					list = tmp2;
				return ;
			}
			list = list->next;
		}
		check_unmap(tmp3);
	}
}
