/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:43:38 by yimizare          #+#    #+#             */
/*   Updated: 2025/02/18 19:22:52 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countlength(long a)
{
	int	count;

	count = 0;
	if (a < 0)
	{
		a *= -1;
		count = 1;
	}
	while (a >= 10)
	{
		count++;
		a /= 10;
	}
	return (count + 1);
}

static char	*writeints(long a, int length, char *string)
{
	int	i;
	int	number;

	i = 0;
	if (a < 0)
	{
		string[0] = '-';
		i++;
		a *= -1;
	}
	while (length > i)
	{
		number = a % 10;
		string[length - 1] = number + '0';
		length--;
		a /= 10;
	}
	return (string);
}

char	*ft_itoa(int n)
{
	long	a;
	char	*itoaed;
	int		length;

	a = n;
	length = countlength(a);
	itoaed = ft_calloc(length + 1, 1);
	if (!itoaed)
		return (NULL);
	itoaed = writeints(n, length, itoaed);
	return (itoaed);
}
