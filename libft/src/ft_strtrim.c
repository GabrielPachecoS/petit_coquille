/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:32:39 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/13 23:51:25 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trim;
	size_t	len_s1;
	size_t	len_trim;
	size_t	first;
	size_t	last;

	first = 0;
	if (!s1 || !set)
		return (NULL);
	len_s1 = ft_strlen(s1);
	last = len_s1 - 1;
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while (s1[last] && ft_strchr(set, s1[last]) && last > first)
		last--;
	len_trim = last - first + 1;
	s1_trim = (char *)malloc(sizeof(char) * (len_trim + 1));
	if (!s1_trim)
		return (NULL);
	ft_strlcpy(s1_trim, &s1[first], len_trim + 1);
	return (s1_trim);
}
