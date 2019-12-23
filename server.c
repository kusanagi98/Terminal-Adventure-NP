#include "helper/mysocket.h"
#include "game/gamemaster.h"
#include "interface/serverfunc.h"

UserNode *root = NULL; //linked list root
#define MAX_CLIENT 30

char users[MAX_CLIENT + 4][STRING_LEN];

int main(int argc, char const *argv[])
{
    bzero(users, (MAX_CLIENT + 4) * STRING_LEN);
    socklen_t clientlen;
    int port;
    /* server's addr */
    struct sockaddr_in serveraddr;
    /* client addr */
    struct sockaddr_in clientaddr;
    /* parent socket */
    int parentfd;
    /* child socket */
    int childfd;
    /* flag value for setsockopt */
    int optval;
    /* max fd set */
    int maxfd;
    /* file descriptor set */
    fd_set master_set;
    /* time val */
    struct timeval tv;
    /* client fd info */
    int client_socket[MAX_CLIENT];
    // char buffer[BUFFER_MAX_LEN];
    UserNode *user;

    /* config server */
    if (argc < 2)
        die("Must provide a port number.\nUsage: ./server <PORT Number>\n", 1);

    port = getPort(argv[1]);

    if (port == -1)
        die("Invalid port number.\n", 1);

    /* Initialize all client_socket[] to zero so not checked */
    for (int i = 0; i < MAX_CLIENT; i++)
    {
        client_socket[i] = 0;
    }

    /* socket create and verification */
    if ((parentfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        die("socket creation failed...\n", 1);
    else
        printf("Socket successfully created..\n");

    optval = 1;
    if (setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR,
                   (const void *)&optval, sizeof(int)) < 0)
    {
        die("set sock opt", 1);
    }

    serveraddr = configAddress("127.0.0.1", port);

    /* Binding newly created socket to given IP and verification */
    if ((bind(parentfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0)
        die("socket bind failed...\n", 1);
    else
        printf("Socket successfully binded..\n");

    /* listen: make this socket ready to accept connection requests */
    if ((listen(parentfd, 5)) != 0)
        die("Listen failed...\n", 1);
    else
        printf("Server listening on %s:%d\n", inet_ntoa(serveraddr.sin_addr), serveraddr.sin_port);

    /* setup time out */
    tv.tv_sec = 3 * 60;
    tv.tv_usec = 0;
    int selectStatus;

    root = loadUserInfo();
    printList(root);
    do
    {
        /* clear fdset */
        FD_ZERO(&master_set);
        /* add parentfd to set */
        FD_SET(parentfd, &master_set);
        maxfd = parentfd;

        /* add child socket to parent */
        for (int i = 0; i < MAX_CLIENT; i++)
        {
            childfd = client_socket[i];
            /* add childfd to fdset */
            if (childfd > 0)
                FD_SET(childfd, &master_set);
            /* set maxfd */
            if (childfd > maxfd)
                maxfd = childfd;
        }

        /* wait activity on one fd */
        selectStatus = select(maxfd + 1, &master_set, NULL, NULL, &tv);

        if ((selectStatus < 0) && (errno != EINTR))
        {
            die("select error", 1);
        }

        if (FD_ISSET(parentfd, &master_set))
        {
            printf("listening\n");
            bzero(&clientaddr, sizeof(clientaddr));
            clientlen = sizeof(clientaddr);
            if ((childfd = accept(parentfd, (struct sockaddr *)&clientaddr, &clientlen)) == -1)
                die("accept error", 1);

            printf("new connection on fd: %d, client info: %s : %d\n",
                   childfd, inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port);

            for (int i = 0; i < MAX_CLIENT; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = childfd;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < MAX_CLIENT; i++)
            {
                if (FD_ISSET(client_socket[i], &master_set))
                {
                    printf("socket .. %d working\n", client_socket[i]);
                    if (handleRequest(client_socket[i], &root) == 0)
                    {
                        /* close socket after user */
                        // printf("close fd %d\n", client_socket[i]);
                        if (strlen(users[client_socket[i]]) > 0)
                        {
                            user = findUser(root, users[client_socket[i]]);
                            user->loggedin = 0;
                            bzero(users[client_socket[i]], STRING_LEN);
                        }
                        close(client_socket[i]);
                        client_socket[i] = 0;
                    }
                }
            }
        }
    } while (1);

    close(parentfd);
    return 0;
}
