/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:12:22 by jucoelho          #+#    #+#             */
/*   Updated: 2025/02/24 21:30:26 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	node;

	node = malloc(sizeof(t_list));
	if (!node)
	{
		perror("Error alocating memory");
		exit(EXIX_FAILURE);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}
