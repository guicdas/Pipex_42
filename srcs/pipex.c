/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:47:23 by gcatarin          #+#    #+#             */
/*   Updated: 2023/07/17 21:43:39 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

static void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main(int ac, char **av, char *envp[])
{
	t_pipex	pipex;

	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	conditions(ac, pipex.infile, pipex.outfile);
	if (pipe(pipex.tube) < 0)
		err("Error with pipe() function");
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	else if (pipex.pid1 < 0)
		err("Error in first fork()");
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, envp);
	else if (pipex.pid2 < 0)
		err("Error in second fork()");
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
}
/*
check path
	printf("->%s\n\n->%s", pipex.paths, pipex.cmd_paths[0]);
pipe
	int main()
	{
		char inbuf[4];
		int p[2], i;
	
		if (pipe(p) < 0)
			exit(1);
	
		write(p[1], "msg1", 4);
		write(p[1], "msg2", 4);
		write(p[1], "msg3", 4);
	
		for (i = 0; i < 3; i++) {
			read(p[0], inbuf, 4);
			printf("%s\n", inbuf);
		}
	}
fork
	fork();
	//fork();
    printf("qualquer coisa\n");
execve
	"which .."
each command
	int main(int ac, char **av, char *envp[])
	{
		t_pipex pipex;
		char *tmp;
		char *command;

		if (ac != 5)
			err("Input Error");
		child_open(&pipex, ac, av);
		if (pipe(pipex.tube) < 0)
			err("Error with pipe() function");
		pipex.paths = find_path(envp);
		pipex.cmd_paths = ft_split(pipex.paths, ':');
		pipex.pid1 = fork();
		if (pipex.pid1 < 0)
			err("Error in first Fork");
		pipex.cmd_args = ft_split(av[2], ' ');
		while (*pipex.cmd_paths)
		{
			tmp = ft_strjoin(*pipex.cmd_paths, "/");
			command = ft_strjoin(tmp, pipex.cmd_args[0]);
			printf("->%s\n-<%s\n", tmp, command);
			free(tmp);
			if (access(command, 0) == 0)
				write(1,"AAAAAAAAAQUI!\n", 15);
			free(command);
			printf("\n");
			pipex.cmd_paths++;
		}
	}
fork pid
	printf("->%d\n", pipex.pid1);
dup2
	int main()
	{
		int fd = open("ex.txt", O_CREAT | O_WRONLY | O_APPEND);
		if(fd < 0)
			err("Error opening the file\n");
		int copy_fd = 1;
		
		dup2(fd, copy_fd);

		write(copy_fd,"This will be output to the file\n", 32);
		write(fd,"This will also be output to the file\n", 37);
	}
*/