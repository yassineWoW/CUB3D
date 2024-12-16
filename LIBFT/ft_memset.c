/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:16:43 by yimizare          #+#    #+#             */
/*   Updated: 2023/12/04 12:36:44 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*string;

	i = 0;
	string = (unsigned char *)b;
	while (i < len)
	{
		string[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int main()
{
	char c = '\0';
	ft_memset(&c, 214, 1);
//ft_memset(&a, *((char *)&m + 2), 3);
//ft_memset(&a, *((char *)&m + 1), 2);
//ft_memset(&a, *((char *)&m), 1);
//ft_memset(&a, m >> 24, 4);
//ft_memset(&a, m >> 16, 3);
//ft_memset(&a, m >> 8, 2);
//ft_memset(&a, m, 1);

printf("%d\n", c);
}

//00000000 00000000 00000101 00111001

// 00000000 00000000 00000101 00111001