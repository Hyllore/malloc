/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/03/20 18:08:53 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//va falloir gerer le fait que dans la liste il faut virer le floor qui a ete unmap
//trouver pourquoi tmp2 fait segfault ce fdp
//ensuite realloc

void	check_unmap()
{
	int check;
	int floor;
	int i;
	void *tmp;
//	t_list *tmp2;

//	tmp2 = list;
	tmp = NULL;
	i = 0;
	floor = list->floor;
	check = 0;
	while (list != NULL)
	{
		tmp = list;
		while (list->floor == floor && list->isfree == 0 && list != NULL)
		{
			printf("test");
			if (i == 10)
			{
				if (list->type == 0)
					munmap(tmp, ((4 * getpagesize()) + (sizeof(t_list) * 100)));
				if (list->type == 1)
					munmap(tmp, ((16 * getpagesize()) + (sizeof(t_list) * 100)));
				if (list->type == 2)
					munmap(tmp, (((list->size + sizeof(t_list) + 1) * getpagesize()) + (sizeof(t_list) * 100)));
//				list = tmp2;
				return ;
			}
			i++;
			list = list->next;
		}
		if (i == 0)
			list = list->next;
		i = 0;
		floor++;
	}
//	list = tmp2;
}

void	ft_free(void *ptr)
{
	t_list *tmp;
	if (list && ptr)
	{
		tmp = list;
		while (list != NULL)
		{
			printf("\nadresses dispos %p\n", list->start);
			printf("\nadresses de tamer la put %p\n", ptr);
			if (list->start == ptr)
			{
				printf("\nslt c 1 test\n");
				list->isfree = 0;
				list = tmp;
				check_unmap();
				return ;
			}
			list = list->next;
		}
		check_unmap();
	}
}
