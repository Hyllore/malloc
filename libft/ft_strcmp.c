/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:10:14 by droly             #+#    #+#             */
/*   Updated: 2017/03/16 16:38:03 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;
	int dst;

	dst = 0;
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	dst = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (dst);
}
