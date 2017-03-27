/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   showalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:23:24 by droly             #+#    #+#             */
/*   Updated: 2017/03/27 18:08:43 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	**putintab(void **add, t_list *tmp, int type)
{
	int i;

	i = 0;
	while (list != NULL)
	{
		if (list->type == type && list->isfree == 1)
		{
			add[i] = &list->start;
			i++;
			add[i] = &list->start[list->size - 1];
			i++;
		}
		list = list->next;
	}
	list = tmp;
	return (add);
}

void	show_alloc_mem()
{
	void **add;
	t_list	*tmp;
	char *ans;

	ans = NULL;
	add = NULL;
	tmp = list;
	add = putintab(add, tmp, 0);
	printf("\nwhat\n");
	ans = ft_itoa_base_ull((long long)&add[0], 16);
	ft_putstr(ans);
	free(ans);
	printf("\nwhat2\n");
	add = NULL;
	add = putintab(add, tmp, 1);
	add = NULL;
	add = putintab(add, tmp, 2);
	//pk segfault
}
