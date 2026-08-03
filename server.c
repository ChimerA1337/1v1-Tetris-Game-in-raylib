#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9000

int main(void) {
    // 1. Create a socket
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) {
        perror("socket failed");
        exit(1);
    }

    // Allow reusing the port immediately after restarting the server
    // (without this, you often get "address already in use" for ~30s after stopping)
    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. Bind the socket to an address + port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // listen on all local interfaces
    address.sin_port = htons(PORT);        // htons = host-to-network byte order

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // 3. Listen for incoming connections
    if (listen(serverFd, 1) < 0) { // 1 = max pending connections in queue
        perror("listen failed");
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);

    // 4. Accept a connection (this BLOCKS until a client connects)
    int clientFd = accept(serverFd, NULL, NULL);
    if (clientFd < 0) {
        perror("accept failed");
        exit(1);
    }

    printf("Client connected!\n");

    char buffer[256] = {0};
    char *reply = "Hello from server!";
    
    
    while(1) {
        if (strcmp(buffer, "End\n") == 0) break;
        memset(buffer, '\0', sizeof(buffer));
        read(clientFd, buffer, sizeof(buffer));
        if(strlen(buffer) != 0) printf("\nRecieved: %s", buffer);
    }

    // 7. Clean up
    close(clientFd);
    close(serverFd);
    return 0;
}