/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:36:00 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/13 23:50:45 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	len_s;
	unsigned int	i;

	i = 0;
	len_s = ft_strlen(s);
	while (s && i < len_s)
	{
		f(i, &s[i]);
			i++;
	}
	s[i] = '\0';
}
