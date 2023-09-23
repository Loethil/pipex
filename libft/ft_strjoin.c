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

	tab = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	// printf("s1 = %ld\n", ft_strlen(s1));
	// printf("s2 = %ld\n", ft_strlen(s2));
	if (!tab)
		return (NULL);
	r = 0;
	a = 0;
	while (s1 && s1[r])
	{
		tab[r] = s1[r];
		r++;
	}
	while (s2 && s2[a])
		tab[r++] = s2[a++];
	tab[r] = '\0';
	return (tab);
}
