/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/03/21 17:03:09 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//va falloir gerer le fait que dans la liste il faut virer le floor qui a ete unmap
//trouver pourquoi tmp2 fait segfault ce fdp
//ensuite realloc

void	find_start(int floor, t_list *tmp2)
{
	printf("\nohfuck2\n");
	t_list *tmp3;

	list = tmp2;
	while (list->next->floor != floor && list->next != NULL)
		list = list->next;
	printf("\nohfuck3\n");
	tmp3 = list->next;
	printf("\nohfuck3.1\n");
	while (tmp3->floor == floor && tmp3->next != NULL)
	{
	printf("\nomg\n");
		tmp3 = tmp3->next;
	}
	printf("\nohfuck4\n");
	list->next = tmp3;
	printf("\nohfuck5\n");
	list = tmp2;
	printf("\nohfuck\n");
}

//faire une fonction qui recherche si il n'y a plus d'element dans list et si premier floor virer remmetre le temporaire au premier element du prochain palier

void	check_unmap(t_list *tmp3)
{
	int check;
	int floor;
	int i;
	void *tmp;
	t_list *tmp2;

	tmp2 = list;
	tmp = NULL;
	i = 0;
	check = 0;
	while (list != NULL)
	{
		printf("\nniktamer\n");
		floor = list->floor;
		tmp = list;
		while (floor == list->floor && list->next != NULL)
		{
			if (list->isfree == 1)
			{
				printf("\nserieux\n");
				check = 1;
				while (list->floor == floor && list->next != NULL)
					list = list->next;
			}
			if (check == 0)
				list = list->next;
			i++;
		}
		if (list->type == 0 && check == 0 && i >= 10)
		{
			printf("\nserieux2\n");
			tmp3 = list;
			find_start(list->floor, tmp2);
			munmap(tmp, ((4 * getpagesize()) + (sizeof(t_list) * 100)));
			if (tmp2)
				list = tmp2;
			printf("\ns?\n");
			return ;
		}
		if (list->type == 1 && check == 0 && i >= 10)
		{
			printf("\nserieux3\n");
			tmp3 = list;
			find_start(list->floor, tmp2);
			munmap(tmp, ((16 * getpagesize()) + (sizeof(t_list) * 100)));
			list = tmp2;
			return ;
		}
		check = 0;
		if (i == 0)
			list = list->next;
		i = 0;
	}
	printf("test de merde%d",tmp2->isfree);
	list = tmp2;
}

void	ft_free(void *ptr)
{
	t_list *tmp2;
	t_list *tmp3;

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
				list = tmp2;
				if (list->type == 2)
				{
					printf("\nserieux4\n");
					tmp3 = list;
					find_start(list->floor, tmp2);
					munmap(tmp3, list->size + sizeof(t_list) + 1);
				}
				else
					check_unmap(tmp3);
				list = tmp2;
				return ;
			}
			list = list->next;
		}
		check_unmap(tmp3);
	}
}
