/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:12:39 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/14 00:03:15 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	len_s;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	new_str = (char *)malloc ((sizeof(char)) * len_s + 1);
	if (!new_str)
		return (NULL);
	while (i < len_s)
	{
		new_str[i] = f(i, s[i]);
			i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
