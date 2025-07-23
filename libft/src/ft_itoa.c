/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:27:31 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/14 00:02:53 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int		len;
	long	num;

	num = n;
	len = 0;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static char	*ft_zero(char *str)
{
	str = (char *)malloc ((sizeof(char)) * 2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static void	ft_fill_str(char *str, long nbr, int i)
{
	while (nbr > 0)
	{
		i--;
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		if (i == 1)
		str[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nbr;

	nbr = n;
	if (nbr == 0)
	{
		str = ft_zero(0);
		return (str);
	}
	else if (nbr < 0)
	{
		nbr = -nbr;
		i = (ft_len(n) + 1);
	}
	else
		i = ft_len(nbr);
	str = (char *)malloc ((sizeof(char)) * i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	ft_fill_str(str, nbr, i);
	return (str);
}
