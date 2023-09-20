/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:04:55 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/15 23:04:58 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		r;
	int		a;

	tab = (char *)malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof (char));
	if (!tab)
		return (NULL);
	r = -1;
	a = -1;
	while (s1[++r])
		tab[r] = s1[r];
	while (s2[++a])
		tab[r++] = s2[a];
	tab[r] = '\0';
	return (tab);
}
