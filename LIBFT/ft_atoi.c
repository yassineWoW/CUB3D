/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:06:01 by yimizare          #+#    #+#             */
/*   Updated: 2025/02/18 19:22:33 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char	*string)
{
	int				i;
	int				ichara;
	unsigned long	result;

	i = 0;
	ichara = 1;
	result = 0;
	while (string[i] == 32 || (string[i] >= 9 && string[i] <= 13))
		i++;
	if (string[i] == '-')
	{
		ichara = -1;
		i++;
	}
	else if (string[i] == '+')
		i++;
	while (ft_isdigit(string[i]))
	{
		result *= 10;
		result += string[i] - '0';
		i++;
	}
	return (result * ichara);
}
