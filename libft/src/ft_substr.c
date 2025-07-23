/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:19:31 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/14 00:01:50 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (!s || start >= len_s || len == 0)
	{
		substr = (char *)malloc ((sizeof(char)) * 1);
		substr[0] = '\0';
		return (substr);
	}
	if (len > len_s - start)
		len = len_s - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
