/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:34:32 by gcatarin          #+#    #+#             */
/*   Updated: 2023/07/17 19:57:20 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	if (dup2(pipex.tube[1], 1) < 0)
		exit(1);
	close(pipex.tube[0]);
	if (dup2(pipex.infile, 0) < 0)
		exit(1);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		if (access(pipex.cmd_args[0], 0) == 0)
		{
			if (execve(pipex.cmd_args[0], pipex.cmd_args, envp) == -1)
				err("Error executing first command");
		}
		else
			command_error(pipex);
	}
	else
	{
		if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
			err("Error executing first command");
	}
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	if (dup2(pipex.tube[0], 0) < 0)
		exit(1);
	close(pipex.tube[1]);
	if (dup2(pipex.outfile, 1) < 0)
		exit(1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		if (access(pipex.cmd_args[0], 0) == 0)
		{
			if (execve(pipex.cmd_args[0], pipex.cmd_args, envp) == -1)
				err("Error executing second command");
		}
		else
			command_error(pipex);
	}
	else
	{
		if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
			err("Error executing second command");
	}
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}
