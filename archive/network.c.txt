#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/network.h"
#include <fcntl.h>
#include "../include/gameState.h"
#include "../include/block.h"

#define PORT 9000

NetworkState *createNetworkState() {
    NetworkState *networkState = malloc(sizeof(NetworkState));
    networkState->connectSocket = -1;
    networkState->socket = -1; // explicitly "no client yet"
    networkState->hostUsername = malloc(24 * sizeof(char));
    networkState->clientUsername = malloc(24 * sizeof(char));
    return networkState;
}

void createHost(NetworkState *networkState) {
    networkState->player = server;

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) { perror("socket failed"); exit(1); }
    
    networkState->connectSocket = serverFd;

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed"); 
        exit(1);
    }
    if (listen(serverFd, 1) < 0) { perror("listen failed"); exit(1); }

    setNonBlocking(serverFd); // key change — don't block on accept() later
}

void createClient(NetworkState *networkState, char *ipString) {
    networkState->player = client;

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        perror("socket failed");
        exit(1);
    }
    networkState->socket = sockFd;

    // 2. Specify the server's address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ipString, &serverAddress.sin_addr) <= 0) {
        perror("invalid address");
        exit(1);
    }

    // 3. Connect to the server
    if (connect(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connection failed");
        exit(1);
    }

    printf("Connected to server!\n");
    setNonBlocking(sockFd);
}

int setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void closeSockets(NetworkState *network) {
    close(network->connectSocket);
    close(network->socket);
}

void freeNetworkState(NetworkState *network) {
    free(network->hostUsername);
    free(network->clientUsername);
    free(network);
}

void sendStart(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    gameState->menuState->whichMenu = multiplayerMenu;
    send(network->socket, "S", sizeof(char), 0);
}

void recieveStart(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    char start;

    int n = read(network->socket, &start, sizeof(char));
    if(n <= 0) return; // no data received, just continue
    if(start == 'S') gameState->menuState->whichMenu = multiplayerMenu;
}

void sendBoardState(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    Board *board = gameState->boards->leftBoard;
    int totalBlocks = board->xBlocks * board->yBlocks;

    Block *block;
    for(int x = 0; x < board->xBlocks; x++) {
        for(int y = 0; y < board->yBlocks; y++) {
            block = copyBlock(board, x, y);
            block->rect.x += 800;
            send(network->socket, block, sizeof(Block), 0);
            free(block);
        }
    }
}

void recieveBoardState(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    Board *board = gameState->boards->rightBoard; // opponent's board, drawn on your screen
    int totalBlocks = board->xBlocks * board->yBlocks;

    size_t expectedBytes = sizeof(Block) * totalBlocks;

    size_t totalRead = 0;
    while (totalRead < expectedBytes) {
        int n = read(network->socket, ((char *)board->blocks) + totalRead, expectedBytes - totalRead);
        if (n <= 0) break; // connection closed or error
        totalRead += n;
    }
}

void lobbyChat(GameState *gameState) {

}