/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:45:44 by jucoelho          #+#    #+#             */
/*   Updated: 2025/02/24 21:47:23 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*first;

	first = *lst;
	if (!lst)
		return ;
	while (first)
	{
		temp = first->next;
		ft_lstdelone(first, del);
		first = temp;
	}
	*lst = NULL;
}
