/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:10:01 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/26 18:10:03 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*rav;

	if (!(*lst))
		return ;
	while (*lst)
	{
		rav = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = rav;
	}
}
