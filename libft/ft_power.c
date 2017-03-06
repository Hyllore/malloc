/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 17:05:46 by droly             #+#    #+#             */
/*   Updated: 2016/02/18 17:06:54 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_power(int n, int power)
{
	int	result;

	if (power < 0 || n == 0)
		return (0);
	if (power == 0)
		return (1);
	result = n;
	while (power != 1)
	{
		result *= n;
		power--;
	}
	return (result);
}
