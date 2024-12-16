#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "echo.h"

void* handleConnection(void* a_client)
{
    int client_fd = *((int*)a_client);
    free(a_client);

    char buffer[BUFFER_SIZE];

    // While loop to constantly receive and echo messages from one connection
    while (1) {
        int bytes_read = read(client_fd, buffer, sizeof(buffer));
        if (bytes_read <= 0) {
            break;
        }
        buffer[bytes_read] = '\0';
        printf("Received: %s", buffer);
        write(client_fd, buffer, bytes_read);
    }

    close(client_fd);
    return NULL;
}