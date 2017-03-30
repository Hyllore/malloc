/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/03/30 16:49:41 by droly            ###   ########.fr       */
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
		tmp3 = tmp3->next;
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
		floor = list->floor;
		tmp = list;
		while (list->next != NULL && floor == list->floor)
		{
			if (list->isfree == 1)
			{
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
			tmp3 = list;
			i2 = find_start(list->floor, tmp2);
			munmap(tmp, ((4 * getpagesize()) + (sizeof(t_list) * 100)));
			if (i2 == 0)
				list = tmp2;
			return (i2);
		}
		if (check == 0 && list->type == 1 && i >= 10)
		{
			tmp3 = list;
			i2 = find_start(list->floor, tmp2);
			munmap(tmp, ((16 * getpagesize()) + (sizeof(t_list) * 100)));
			if (i2 == 0)
				list = tmp2;
			return (i2);
		}
		check = 0;
		if (i == 0)
			list = list->next;
		i = 0;
	}
	list = tmp2;
	return (0);
}

//commande cat segfault dans free, commande ls / segfault quelque part, commande htop possible que ce soit calloc, quoi que c possible que ce soit realoc, faire calloc, et etre fixer

void		free(void *ptr)
{
	t_list	*tmp2;
	t_list	*tmp3;
	int		i;

	i = 0;
	tmp3 = NULL;
	ft_putstr("\nfree\n");
	if (list && ptr)
	{
		ft_putstr("\nfree 1er if\n");
		tmp2 = list;
		while (list != NULL)
		{
			ft_putstr("\nfree while\n");
			if (list->start == ptr)
			{
				ft_putstr("\nfree 2eme if\n");
				list->isfree = 0;
				ft_putnbr(list->type);
				if (list->type == 2)
				{
					ft_putstr("\nfree 3er if\n");
					tmp3 = list;
					find_start(list->floor, tmp2);
					munmap(tmp3, tmp3->size + sizeof(t_list) + 1);
					i = 1;
					return ;
				}
				else
				{
					ft_putstr("\nfree else\n");
					list = tmp2;
					i = check_unmap(tmp3);
				}
				if (i == 0)
					list = tmp2;
//				show_alloc_mem();
				ft_putstr("\nfree out\n");
				return ;
			}
			ft_putstr("\nfree next avant\n");
			list = list->next;
			ft_putstr("\nfree next apres\n");
		}
//		list = tmp2;
		ft_putstr("\nfree out of while\n");
		i = check_unmap(tmp3);
		ft_putstr("\nfree out of while\n");
//		if (i == 0)
//			list = tmp2;
	}
//	list = tmp2;
	ft_putstr("\nfree out 2\n");
}
