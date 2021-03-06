/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:09:32 by droly             #+#    #+#             */
/*   Updated: 2017/03/27 17:21:10 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_putstr(char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return ;
	while (str[index] != '\0')
	{
		ft_putchar(str[index]);
		index++;
	}
}
