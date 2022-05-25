/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shitdealer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:02:45 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/05/11 17:48:19 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_here(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->path[++i])
		free (p->path[i]);
	free (p->path);
	close(p->infile);
	close(p->outfile);
}

void	free_all(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->path[++i])
		free (p->path[i]);
	free (p->path);
	i = -1;
	while (p->arg[++i])
		free (p->arg[i]);
	free (p->arg);
	close(p->infile);
	close(p->outfile);
}

void	err(t_pipex *p, char *s)
{
	perror(s);
	if (p->here_doc)
		free_here(p);
	else
		free_all(p);
	exit(EXIT_FAILURE);
}

void	special_err(t_pipex *p, char *s)
{
	perror(s);
	free_here(p);
	exit(EXIT_FAILURE);
}

void	err_all(t_pipex *p, char *s)
{
	perror(s);
	free_all(p);
	exit(EXIT_FAILURE);
}
