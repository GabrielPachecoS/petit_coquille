/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:36:50 by jucoelho          #+#    #+#             */
/*   Updated: 2025/02/24 21:41:47 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstad_back(t_list **lst, t_list *new)
{
	while (new)
	{
		new->next = *lst;
		*lst = new;
	}
	if (new == NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}
