#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void putstr_fd(int fd, const char *str){
		write(fd, str, strlen(str));
}

int main(int argc, const char **argv){

	if (argc != 2){
		putstr_fd(STDERR_FILENO, "Wrong number of arguments\n");
		exit(1);
	}

	int sockfd, connfd, port, id;
	struct sockaddr_in servaddr, cli; 

	port = atoi(argv[1]);
	if (port == 0){
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1);
	}

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1); 
	}

	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1); 
	} 

	if (listen(sockfd, 10) != 0){
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1); 
	}
	
	return (0);
}