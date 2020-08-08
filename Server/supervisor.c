


#include "stable_network/c_version.h"
#include "supervisor.h"

char    *create_filename(int socket)
{
    char *filename = strdup(".hiddenX");

    filename[7] = socket + '0';
    return (filename);
}

void    send_output(int sockfd, char *filename)
{
    unsigned char    *buffer;
    int     fd;
    struct stat info;
    size_t  size;

    fd = open(filename, O_RDONLY);
    fstat(fd, &info);
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * info.st_size + 1);
    size = read(fd, buffer, info.st_size);
    buffer[size] = '\0';
    close(fd);
    StableSend(sockfd, buffer, size);
    free(buffer);
}

void    accept_fork(int socket)
{
    t_goldilox  *network;
    char        *filename;
    int         fd;
    char        **env;
    int         output;
    int         error;
    
    env = init();
    filename = create_filename(socket);
    while (true)
    {
        // create file to store terminal output.
        fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);

        // route all output and error to the opened file.
        output = dup(1);
        error = dup(2);
        dup2(fd, 1);
        dup2(fd, 2); 
        
        // receive command from client.
        network = StableRecv(socket);   
        network->content[network->size] = '\0';

        // run the shell command received.
        shell(env, (char *)network->content);
        
        // output form shell sent to file, send contents of file.
        send_output(socket, filename);

        // reset, repeat.
        free(network->content);
        free(network);
        dup2(output, 1);
        dup2(error, 2);
        close(fd);
        remove(filename); 
    }
}

int     main(void)
{
    int                 servfd;
    struct sockaddr_in  server_address;
    int                  asock;
    pid_t                pid;

    servfd = InitServer(4242, 5, &server_address);
    while (true)
    {
        asock = HandshakeAccept(servfd, server_address);
        if ((pid = fork()) == 0)
        {
            printf("client connected\n");
            printf("forking...\n");
            accept_fork(asock);
        }
    }
    return (0);
}














