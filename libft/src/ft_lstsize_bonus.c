/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:11:46 by jucoelho          #+#    #+#             */
/*   Updated: 2025/06/02 21:31:48 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	nbr_nodes;

	nbr_nodes = 0;
	while (lst)
	{
		lst = lst->next;
		nbr_nodes++;
	}
	return (nbr_nodes);
}
