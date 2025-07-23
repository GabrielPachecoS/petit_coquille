/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:47:36 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/14 00:08:22 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*scopy;
	size_t	len;

	len = (ft_strlen(s) + 1);
	scopy = (char *)malloc ((sizeof(char)) * (len));
	if (!scopy)
		return (NULL);
	ft_strlcpy(scopy, s, len);
	return (scopy);
}
