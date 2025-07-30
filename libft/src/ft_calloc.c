/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:10:45 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/30 19:12:46 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	nmemb_size;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	nmemb_size = nmemb * size;
	array = (char *) ((sizeof(char)) * nmemb_size);
	if (!array)
		return (NULL);
	ft_bzero(array, nmemb_size);
	return (array);
}
