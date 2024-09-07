/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:56:49 by gcatarin          #+#    #+#             */
/*   Updated: 2023/07/17 19:57:25 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "!\n", 2);
	exit(0);
}

void	conditions(int ac, int infile, int outfile)
{
	if (ac != 5)
		err("Input Error");
	if (infile < 0)
		err("Error opening infile");
	if (outfile < 0)
		err("Error opening outfile");
}

void	command_error(t_pipex pipex)
{
	write(2, "Command not found: ", 19);
	write(2, pipex.cmd_args[0], ft_strlen(pipex.cmd_args[0]));
	child_free(&pipex);
}
