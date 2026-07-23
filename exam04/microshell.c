#include "unistd.h"
#include "string.h"
#include "sys/wait.h"
#include "stdlib.h"

void ft_putstr_err(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
}

void exec(char **argv, char **envp, int i, int tmp_fd)
{
	argv[i] = NULL;
	if (dup2(tmp_fd, STDIN_FILENO) == -1)
	{
    	ft_putstr_err("error: fatal", NULL);
    	exit(1);
	}
	close(tmp_fd);
	execve(argv[0], argv, envp);
	ft_putstr_err("error: cannot execute ", argv[0]);
	exit(1);
}

int main(int argc, char **argv, char **envp)
{
	int i;
	int fd[2];
	int tmp_fd;
	pid_t pid;
	(void)argc;

	i = 0;

	// On sauvegarde le STDIN de base
	tmp_fd = dup(STDIN_FILENO);
	if (tmp_fd == -1)
	{
	    ft_putstr_err("error: fatal", NULL);
	    exit(1);
	}

	while (argv[i] && argv[i + 1])
	{
		// Reset argv
		argv = &argv[i + 1];
		i = 0;

		// On parse jusqu'a la prochaine semicolon ou pipe
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;

		// Custom CD
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 2)
				ft_putstr_err("error: cd: bad arguments", NULL);
			else if (chdir(argv[1]))
				ft_putstr_err("error: cd: cannot change directory to ", argv[1]);
		}

		// Exec semi colon ou derniere commande
		else if ((i != 0 && argv[i] == NULL) || strcmp(argv[i], ";") == 0)
		{
			// Child process qui exec
			pid = fork();
			if (pid == 0)
				exec(argv, envp, i, tmp_fd);
			else if (pid == -1)
			{
				ft_putstr_err("error: fatal", NULL);
    			exit(1);
			}

			// Parent process
			else 
			{
				close(tmp_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1);
				tmp_fd = dup(STDIN_FILENO);
				if (tmp_fd == -1)
				{
				    ft_putstr_err("error: fatal", NULL);
				    exit(1);
				}
			}
		}

		// Exec pipe
		else if (i != 0 && strcmp(argv[i], "|") == 0)
		{

			if (pipe(fd) == -1)
			{
		    	ft_putstr_err("error: fatal", NULL);
		    	exit(1);
			}

			// Child process
			pid = fork();
			if (pid == 0)
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
				{
				    ft_putstr_err("error: fatal", NULL);
				    exit(1);
				}
				close(fd[0]);
				close(fd[1]);
				exec(argv, envp, i, tmp_fd);
			}
			else if (pid == -1)
			{
				ft_putstr_err("error: fatal", NULL);
    			exit(1);
			}

			// Parent process
			else 
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}