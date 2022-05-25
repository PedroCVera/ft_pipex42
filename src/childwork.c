/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childwork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:59:32 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/05/18 18:59:39 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	goodshit(t_pipex *p)
{
	int		ind;
	char	*tmp;

	ind = -1;
	while (p->path[++ind])
	{
		tmp = ft_strjoin(p->path[ind], p->cmdpath);
		if (access(tmp, F_OK) >= 0)
		{
			p->cmdpath = ft_strdup(tmp);
			free (tmp);
			return ;
		}
		free (tmp);
	}
	special_err(p, "Error");
}

void	criancasfelizes(t_pipex *p)
{
	if (0 > access(p->cmdpath, F_OK))
		err_all(p, "Error");
}

void	child_work(t_pipex *p, int i)
{
	int	ind;

	ind = 0;
	if (p->arg[i][0] == '/')
	{
		while (p->arg[i][ind] && p->arg[i][ind] != ' ')
			ind++;
		p->cmdpath = ft_substr(p->arg[i], 0, ind);
		p->cmd = ft_split(ft_strrchr(p->arg[i], '/') + 1, ' ');
		criancasfelizes(p);
	}
	else
	{
		p->cmd = ft_split(p->arg[i], ' ');
		p->cmdpath = ft_strjoin("/", p->cmd[0]);
		goodshit(p);
	}
}
