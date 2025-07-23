/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:36 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/24 22:18:26 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	k = 0;
	while (src[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (dst[i] != '\0')
		i++;
	if (i >= size)
		return (j + size);
	while ((i + k < size - 1) && (src[k] != '\0'))
	{
		dst[i + k] = src[k];
			k++;
	}
	dst[i + k] = '\0';
	return (i + j);
}
