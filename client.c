#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9000

int main(void) {
    // 1. Create a socket
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        perror("socket failed");
        exit(1);
    }

    // 2. Specify the server's address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert "127.0.0.1" (localhost) into the required binary format
    if (inet_pton(AF_INET, "192.168.0.40", &serverAddress.sin_addr) <= 0) {
        perror("invalid address");
        exit(1);
    }

    // 3. Connect to the server
    if (connect(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connection failed");
        exit(1);
    }

    printf("Connected to server!\n");

    // 4. Send a message
    char *message = "Hello from client!";
    send(sockFd, message, strlen(message), 0);

    // 5. Receive the reply
    char buffer[256] = {0};
    
    printf("Received: %s\n", buffer);

    while (1) {
        memset(buffer, '\0', sizeof(buffer));
        printf("\nSend a message: ");
        fgets(buffer, sizeof(buffer), stdin);
        if(strcmp(buffer, "End\n") == 0) break;
        send(sockFd, buffer, strlen(message), 0);
    }

    // 6. Clean up
    close(sockFd);
    return 0;
}