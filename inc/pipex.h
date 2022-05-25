/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:15:38 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/05/16 14:59:03 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/gnl/get_next_line.h"
# include <stdio.h>

# define BUFFER_SIZE 10

//struct to be able to use each variable
//after parsing them anywhere else in
//the program

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		pipe[2];
	int		lastcmd;
	int		cmdnbr;
	int		in;
	int		out;
	char	**arg;
	char	*env;
	int		id;
	pid_t	pid;
	char	**cmd;
	char	**path;
	char	*cmdpath;
	char	*limiter;
}		t_pipex;

//	parsing.c

void	ft_findpath(t_pipex *p, char **envp);
void	parsingpipex(t_pipex *p, char **argv, int argc);
void	nodoc(t_pipex *p, char **argv, int argc);
void	hellodoc(t_pipex *p, char **argv, int argc);
void	heredocfiller(int tempfile, char **argv);

//	childwork.c

void	criancasfelizes(t_pipex *p);
void	goodshit(t_pipex *p);
void	child_work(t_pipex *p, int i);

//	pipex.c

void	child_labor(t_pipex *p, int i, char **envp);
void	wrongstart(void);

//	shitdealer.c

void	err_all(t_pipex *p, char *s);
void	special_err(t_pipex *p, char *s);
void	err(t_pipex *p, char *s);
void	free_all(t_pipex *p);
void	free_here(t_pipex *p);

#endif
