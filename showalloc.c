/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   showalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:23:24 by droly             #+#    #+#             */
/*   Updated: 2017/03/30 16:47:18 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		showadd(void *str)
{
	str = ft_itoa_base_ull((unsigned long long)str, 16);
	ft_putstr(str);
	free(str);
}

void		begin_type(int type, char *str)
{
	if (type == 0)
		ft_putstr("TINY : 0x");
	if (type == 1)
		ft_putstr("SMALL : 0x");
	if (type == 2)
		ft_putstr("LARGE : 0x");
	str = ft_itoa_base_ull((unsigned long long)list, 16);
	ft_putstr(str);
	free(str);
	ft_putchar('\n');
}

void		middle_type(char *str)
{
	ft_putstr("0x");
	str = ft_itoa_base_ull((unsigned long long)list->start, 16);
	ft_putstr(str);
	free(str);
	ft_putstr(" - 0x");
	str = ft_itoa_base_ull((unsigned long long)&list->start[list->size], 16);
	ft_putstr(str);
	free(str);
	ft_putstr(" : ");
	ft_putnbr(list->size);
	ft_putstr(" octets\n");
}

void		putintab(t_list *tmp, int type)
{
	int		i;
	char	*str;
	int		floor;

	floor = -1;
	str = NULL;
	i = 0;
	while (list != NULL)
	{
		if (list->type == type && list->floor != floor)
			begin_type(type, str);
		floor = list->floor;
		if (list->type == type && list->isfree == 1)
			middle_type(str);
		list = list->next;
	}
	list = tmp;
}

void		show_alloc_mem(void)
{
	t_list	*tmp;
	char	*ans;

	ans = NULL;
	tmp = list;
	putintab(tmp, 0);
	putintab(tmp, 1);
	putintab(tmp, 2);
}
