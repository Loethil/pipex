/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:15:37 by mbatteux          #+#    #+#             */
/*   Updated: 2023/09/20 18:15:39 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	**add_slash(char **all_path)
{
	int	i;
	int	j;

	i = 0;
	while (all_path[i])
	{
		j = ft_strlen(all_path[i]);
		all_path[i][j++] = '/';
		all_path[i][j] = '\0';
		i++;
	}
	return (all_path);
}

char	**find_path(char **env, char **all_path)
{
	int	i;

	if (!all_path)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
			break;
		i++;
	}
	all_path = ft_split(env[i] + 5, ':');
	all_path = add_slash(all_path);
	return (all_path);
}

char	*get_access(char *tab, char **all_path, char *argv)
{
	int	i;

	i = 0;
	while(all_path[i])
	{
		tab = ft_strjoin(all_path[i], argv);
		if (access(tab, X_OK) == 0)
			break ;
		else if (access(tab, X_OK) == -1)
			tab = NULL;
		i++;
	}
	return (tab);
}