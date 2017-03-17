/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/03/17 11:44:34 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
				return ;
			}
			list = list->next;
		}
	}
}
