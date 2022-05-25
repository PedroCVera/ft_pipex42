/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:20:29 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/05/18 15:20:35 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* This function fills the tempfile with the text to be
	pr as an infile, basically "taking" an infile */

void	heredocfiller(int tempfile, char **argv)
{
	char	*buf;
	char	*tmp;

	tmp = ft_strjoin(argv[2], "\n");
	while (1)
	{
		write(1, "pipe to heredoc> ", 17);
		buf = get_next_line(0);
		if (buf)
		{
			if (ft_strncmp(buf, tmp, ft_strlen(tmp)) == 0)
				break ;
			write(tempfile, buf, ft_strlen(buf));
			free(buf);
		}
		else
			break ;
	}
	free (tmp);
	if (buf)
		free (buf);
}

/*	This function is activated when the program
	detects the option with a "here_doc", it starts
	by creating a temporary and invisible file ".*_tmp"
	that will be sent to the function above to get filled,
	then it will close the first open as it has the wrong
	opening setting and will set it as an infile, which
	needs the permission read only instead of write
	only.*/

void	hellodoc(t_pipex *p, char **argv, int argc)
{
	int	tempfile;

	if (argc < 6)
		wrongstart();
	p->here_doc = 1;
	tempfile = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	p->outfile = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tempfile < 0 || p->outfile < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	heredocfiller(tempfile, argv);
	close (tempfile);
	p->infile = open(".heredoc_tmp", O_RDONLY);
	if (p->infile < 0)
	{
		unlink(".heredoc_tmp");
		exit(EXIT_FAILURE);
	}
}

/*	The first option as the mandatory part says
	is no here_doc, so i created this function to
	deal with the more simple cases where there is
	no need to create any temporary file to host
	here_doc, setting the infile to the one given
	permissions to read only.
	Also setting the outfile to write only, to always
	create a new line (in case the file already exists,
	if not, it creates it w (O_CREAT)) and to write
	from that line*/

void	nodoc(t_pipex *p, char **argv, int argc)
{
	p->here_doc = 0;
	p->infile = open (argv[1], O_RDONLY);
	p->outfile = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->infile < 0 || p->outfile < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

/*	This function checks both option for function call
	both the "here_doc" version and the simple one with
	only infile, outfile and cmds, it redirects to
	secondary functions in different case scenarios.
	After that is out of the way it will set up the args*/

void	parsingpipex(t_pipex *p, char **argv, int argc)
{
	int	ind;
	int	jnd;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		hellodoc(p, argv, argc);
	else
		nodoc(p, argv, argc);
	p->arg = malloc(sizeof(char *) * argc);
	if (!p->arg)
		err(p, "Error");
	ind = 1;
	jnd = -1;
	while (++ind < argc)
		p->arg[++jnd] = ft_strdup(argv[ind]);
	p->arg[++jnd] = 0;
}

/*	This function will go through all the lines sent
	by envp in search for the "PATH" line and will
	copy it all to the string s apart from the
	first 5 characters "PATH:" then it will
	process to keep every part of the path
	in the matrix p->path (separated by each ":"*/

void	ft_findpath(t_pipex *p, char **envp)
{
	char	*s;
	int		ind;

	ind = -1;
	while (envp[++ind])
		if (!ft_strncmp(envp[ind], "PATH", 4))
			s = ft_strdup(envp[ind] + 5);
	if (!s)
		err(p, "Error");
	p->path = ft_split(s, ':');
	free (s);
}
