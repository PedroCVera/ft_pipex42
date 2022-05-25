/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:13:40 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/05/18 15:13:42 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	wrongstart(void)
{
	ft_putstr_fd("The correct way to start this function is:\
 ./pipex infile command1 command2 outfile\n", 2);
	exit(EXIT_FAILURE);
}

void	child_labor(t_pipex *p, int i, char **envp)
{
	if (pipe(p->pipe) == -1)
		err(p, "Error");
	p->pid = fork();
	if (p->pid < 0)
		err(p, "Error");
	if (!p->pid)
	{
		close(p->pipe[0]);
		if (p->id == 0)
		{
			dup2(p->infile, STDIN_FILENO);
			dup2(p->pipe[1], STDOUT_FILENO);
		}
		else if (p->id == p->cmdnbr - 1)
			dup2(p->outfile, STDOUT_FILENO);
		else
			dup2(p->pipe[1], STDOUT_FILENO);
		child_work(p, i);
		execve(p->cmdpath, p->cmd, envp);
		free_all(p);
		exit(127);
	}
	close (p->pipe[1]);
	dup2(p->pipe[0], STDIN_FILENO);
	close(p->pipe[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		ind;

	if (argc < 5)
		wrongstart();
	parsingpipex(&p, argv, argc);
	p.cmdnbr = argc - p.here_doc - 3;
	ft_findpath(&p, envp);
	p.id = -1;
	while (++p.id < p.cmdnbr)
		child_labor(&p, p.id + p.here_doc, envp);
	close(0);
	waitpid(p.pid, NULL, 0);
	ind = 0;
	while (ind++ < p.cmdnbr - 1)
		wait(NULL);
	if (p.here_doc)
		unlink(".heredoc_tmp");
	free_all(&p);
	return (0);
}
