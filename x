// void	_cmds(char **paths, t_cmd *commands)
// {
// 	pid_t pid;
// 	int fd[2];
// 	char *path;
// 	int inp = dup(0), out = dup(1);
// 	while (commands)
// 	{
// 		if (commands->next)
// 		{
// 			if (pipe(fd) == -1)
// 			{
// 				perror("minishell: pipe");
// 				exit(1);
// 			}
// 		}
// 		if ((pid = fork()) == -1)
// 		{
// 			perror("minishell: fork");
// 			exit(1);
// 		}
// 		if (pid == 0)
// 		{
// 			if (commands->next)
// 			{
// 				close(fd[0]);
// 				dup2(fd[1], 1);
// 			}
// 				path = find_path(paths, commands->cmd[0]);
// 				if(!path)
// 				{
// 					ft_err(commands);
// 					exit(0);
// 				}
// 				check_redir(commands);
// 				exec_cmd(commands, path);
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			if (commands->next)
// 			{
// 				close(fd[1]);
// 				// if(commands->inp == 0)
// 				dup2(fd[0], 0);
// 			}
// 		}
// 		commands = commands->next;
// 	}
// 	(dup2(out, 1), dup2(inp, 0));
// 	(close(out), close(inp));
// }