#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	throw_error(char *err, char *arg)
{
	int	i;

	i = 0;
	while (err[i])
		write(STDERR_FILENO, &err[i++], 1);
	if (arg)
	{
		i = 0;
		while (arg[i])
			write(STDERR_FILENO, &arg[i++], 1);
	}
	write(STDERR_FILENO, "\n", 1);
}

int	exec_last_cmd(char **argv, char **envp)
{
	if (execve(argv[0], argv, envp) == -1)
	{
		throw_error("error: cannot execute ", argv[0]);
		return (1);
	}
	return (0);
}

void	exec_semicolon(char **argv, char **envp, int end)
{
	pid_t pid;

	argv[end] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, envp) == -1)
		{
			throw_error("error: cannot execute ", argv[0]);
			exit(1);
		}
	}
	waitpid(pid, NULL, 0);
}

void	exec_pipe(void)
{
}

int	get_cmd_end(char **argv, int start)
{
	int	i;

	i = start;
	while (argv[i])
	{
		if (argv[i][0] == ';' || argv[i][0] == '|')
			return (i);
		i++;
	}
	return (i);
}

int	custom_cd(char **argv, int argc)
{
	if (argc != 3)
		return (throw_error("error: cd: bad arguments", NULL), 1);
	else if (chdir(argv[2]) != 0)
		return (throw_error("error: cd: cannot change directory to ", argv[2]),
			1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	end;

	end = 0;
	if (argc < 2)
		return (0);
	if (strcmp(argv[1], "cd") == 0)
		return (custom_cd(argv, argc));
	else
	{
		i = 1;
		while (argv[i])
		{
			end = get_cmd_end(argv, i);
			if (argv[end] == NULL)
				return (exec_last_cmd(argv + i, envp), 0);
			else if (argv[end][0] == ';')
				exec_semicolon(argv + i, envp, end - i);
			else if (argv[end][0] == '|')
				exec_pipe();
			i = end + 1;
		}
	}
	return (0);
}
