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

void broadcast(int sender, int max_fd, fd_set writeSet, char *str) {
    for (int fd = 0; fd <= max_fd; fd++)
        if (FD_ISSET(fd, &writeSet) && fd != sender)
            send(fd, str, strlen(str), 0);
}


int main(int argc, const char **argv) {

	// Check the number of arguments
	if (argc != 2){
		putstr_fd(STDERR_FILENO, "Wrong number of arguments\n");
		exit(1);
	}

	// socket create and verification 
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1){
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1);
	}
		
	int port = atoi(argv[1]);
	if (port == 0){
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1);
	}

	// assign IP, PORT 
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1);
	}
	
	if (listen(sockfd, 10) != 0) {
		putstr_fd(STDERR_FILENO, "Fatal error\n");
		exit(1);
	}

	int  ids[65536];      // ids[fd] = client id
	char *msgs[65536];    // msgs[fd] = that client's pending buffer (for partial lines)
	int  next_id = 0;     // the next id to hand out; it only ever goes up
	int  max_fd = sockfd;	  // Highest current fd 

	// Select overwrites the set that is passed so keep the master copy safe
	fd_set active;
	fd_set readSet;
	fd_set writeSet;

	FD_ZERO(&active);
	FD_SET(sockfd, &active);

	while (1)
	{
		// Reset the sets on each iteration
		readSet = active;
		writeSet = active;

		// Check if any of the sockets are ready to read or write
		if (select(max_fd + 1, &readSet, &writeSet, NULL, NULL) < 0)
			continue;
		
		for (int fd = 0; fd <= max_fd; fd++){

			if (!FD_ISSET(fd, &readSet))
				continue;
			
			// if listening socket, try to accept the new client
			if (fd == sockfd)
			{
				// Try and check that the connection has been established
				int cli = accept(sockfd, NULL, NULL);
				if (cli < 0)
					continue;
				
				if (cli > max_fd)
					max_fd = cli;
				
				// Add the new client to the active set and give him his id
				FD_SET(cli, &active);
				ids[cli] = next_id++;

				// Set the client msgs buffer to NULL
				msgs[cli] = NULL;

				// Broadcast the arrival of the new client to the other users
				char buf[64];
				sprintf(buf, "server: client %d just arrived\n", ids[cli]);
				broadcast(cli, max_fd, writeSet, buf);
			}
			else 
			{
				char buf[4096 + 1];

				// Try to read data from the socket
				int n = recv(fd, buf, 4096, 0);
				if (n <= 0)
				{
					// Append disconnection msg to buf and broadcast
					sprintf(buf, "server: client %d just left\n", ids[fd]);
					broadcast(fd, max_fd, writeSet, buf);

					// Cleanup
					FD_CLR(fd, &active);
					FD_CLR(fd, &writeSet);
					free(msgs[fd]);
					msgs[fd] = NULL;
					close(fd);
				} 
				else 
				{
					// Null terminate the buffer
				    buf[n] = '\0';
				    msgs[fd] = str_join(msgs[fd], buf);
					if (!msgs[fd]){
						putstr_fd(STDERR_FILENO, "Fatal error\n");
						exit(1);
					}
				    
					// Extract each messages and broadcast them
					char *line;
					int ret;
				    while ((ret = extract_message(&msgs[fd], &line)) == 1)
					{
						char prefix[32];
    					sprintf(prefix, "client %d: ", ids[fd]);

    					broadcast(fd, max_fd, writeSet, prefix);
    					broadcast(fd, max_fd, writeSet, line);
    					free(line);
				    }
					
					// Check for extract malloc failure
					if (ret == -1){
						putstr_fd(STDERR_FILENO, "Fatal error\n");
						exit(1);
					}
				}
			}
		}
	}

	return (0);
}