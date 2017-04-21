/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:04:08 by droly             #+#    #+#             */
/*   Updated: 2017/04/21 10:00:31 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			find_start(int floor, t_list *tmp2)
{
	t_list	*tmp3;

	list = tmp2;
	if (list->floor == floor)
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
	t_list	*tmp2;

	i2 = 0;
	tmp2 = list;
	i = 0;
	check = 0;
	while (list != NULL)
	{
		floor = list->floor;
		tmp3 = list;
//		ft_putstr("\nentre\n");
		while (list->next != NULL && floor == list->floor)
		{
//			ft_putstr("\ntourne\n");
			if (list->isfree == 1)
			{
//				ft_putstr("\ncheck\n");
				check = 1;
				while (list->next != NULL && list->floor == floor)
					list = list->next;
			}
			if (check == 0)
				list = list->next;
			i++;
		}
		if (list->isfree == 1 && list->floor == floor)
		{
//			ft_putstr("\ncheck 2\n");
			check = 1;
		}
//			ft_putstr("\nfin\n");
		if (check == 0 && tmp3->type == 0 && i >= 10)
		{
//			tmp3 = list;
//			ft_putstr("\n---unmap floor type 0 ->");
			ft_putnbr(tmp3->floor);
			find_start(tmp3->floor, tmp2);
//			ft_putstr("\n---unmap floor ->");
//			ft_putnbr(list->floor);
			ft_putchar('\n');
			if (munmap(tmp3, ((4 * getpagesize()) + (sizeof(t_list) * 100))) == -1)
			{
//				ft_putstr("\nunmap failed\n");
				return (0);
			}
//			if (i2 == 0)
//				list = tmp2;
			return (i2);
		}
		if (check == 0 && tmp3->type == 1 && i >= 10)
		{
//			tmp3 = list;
//			ft_putstr("\n---unmap floor type 1->");
			ft_putnbr(tmp3->floor);
			find_start(tmp3->floor, tmp2);
//			ft_putstr("\n---unmap floor ->");
//			ft_putnbr(list->floor);
			ft_putchar('\n');
			if (munmap(tmp3, ((16 * getpagesize()) + (sizeof(t_list) * 100))) == -1)
			{
//				ft_putstr("\nunmap failed\n");
				return (0);
			}
//			if (i2 == 0)
//				list = tmp2;
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
//	ft_putstr("\nfree\n");
	tmp2 = list;
	if (list && ptr)
	{
//		ft_putstr("\nfree 1er if\n");
		while (list != NULL)
		{
//			ft_putstr("\nfree while\n");
			if (list->start == ptr)
			{
//				ft_putstr("\nfree 2eme if\n");
				list->isfree = 0;
//				ft_putnbr(list->type);
				if (list->type == 2)
				{
//					ft_putstr("\nfree 3er if\n");
					tmp3 = list;
//					ft_putstr("\n---unmap floor ->");
//					ft_putnbr(list->floor);
					find_start(list->floor, tmp2);
//					ft_putchar('\n');
					if ((munmap(tmp3, tmp3->size + sizeof(t_list) + 1)) == -1)
					{
//						ft_putstr("\nunmap failed\n");
						return ;
					}
					return ;
				}
				else if (list->type == 1 || list->type == 0)
				{
//					ft_putstr("\nfree else\n");
					list = tmp2;
					check_unmap(NULL);
					return ;
				}
//				if (i == 0)
				list = tmp2;
//				show_alloc_mem();
//				ft_putstr("\nfree out\n");
				return ;
			}
//			ft_putstr("\nfree next avant\n");
			list = list->next;
//			ft_putstr("\nfree next apres\n");
		}
//		list = tmp2;
//		ft_putstr("\nfree out of while\n");
//		i = check_unmap(tmp3);
//		ft_putstr("\nfree out of while\n");
//		if (i == 0)
//			list = tmp2;
	}
	list = tmp2;
//	ft_putstr("\nfree out 2\n");
}

//bon putain ca segfault bordle de merde ya eu des changements et une refonte de toute la fonction free pacque ya des trucs ct de la merde pareil pour add new 2 enfin bon cer projet ca me les brises je sais pas ce que jai oublier mais bon
