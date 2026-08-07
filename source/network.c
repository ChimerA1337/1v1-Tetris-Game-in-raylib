#include <enet/enet.h>
#include <stdio.h>
#include "../include/network.h"
#include "../include/gameState.h"
#include "../include/tetrisLogic.h"
#include "../include/preview.h"
#include "../include/definitions.h"
#include <stdlib.h>
#include <time.h>
#include "../include/block.h"


void initializeENet() {
    if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        exit(EXIT_FAILURE);
    }
    atexit(enet_deinitialize);
}

NetworkState *createNetworkState() {
    NetworkState *networkState = malloc(sizeof(NetworkState));

    networkState->hostUsername = malloc(25 * sizeof(char));
    networkState->clientUsername = malloc(25 * sizeof(char));
    networkState->hostUsername[0] = '\0';
    networkState->clientUsername[0] = '\0';
    networkState->player = client; // default to client, can be changed later
    return networkState;
}

void createHost(NetworkState *networkState) {
    networkState->player = server;

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 9000;

    networkState->host = enet_host_create(&address, 1, 2, 0, 0);
    if (networkState->host == NULL) {
        fprintf(stderr, "Failed to create ENet host\n");
        exit(1);
    }

    printf("Server listening on port 9000...\n");
}

void createClient(NetworkState *networkState, const char *ipString) {
    networkState->player = client;

    // Create a client host (NULL address means "pick any local address")
    networkState->host = enet_host_create(NULL, 1, 2, 0, 0);
    if (networkState->host == NULL) {
        fprintf(stderr, "Failed to create ENet host\n");
        exit(1);
    }

    ENetAddress address;
    enet_address_set_host(&address, ipString);
    address.port = 9000;

    // Connect to the server
    ENetPeer *peer = enet_host_connect(networkState->host, &address, 2, 0);
    if (peer == NULL) {
        fprintf(stderr, "Failed to connect\n");
        exit(1);
    }

    printf("Connecting to %s...\n", ipString);
}

void pollNetworkEvents(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    if (network->host == NULL) return;

    ENetEvent event;
    while (enet_host_service(network->host, &event, 0) > 0) {  // 0 = non-blocking
        printf("Event type: %d\n", event.type);
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("Client connected!\n");
                printf("Connection channel: %d\n", event.channelID);
                network->peer = event.peer;
                // maybe close the "waiting for connection" prompt here
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("Client disconnected\n");
                network->peer = NULL;
                break;
            case ENET_EVENT_TYPE_RECEIVE: {
                // Handle incoming data (usernames, board state, etc.)
                ENetPacket *packet = event.packet;
                printf("Received %zu bytes\n", packet->dataLength);
                printf("Packet channel: %d\n", event.channelID);
                
                switch(event.channelID) {
                    case NET_MESSAGE_CHANNEL:
                        printf("Received NetMessage\n");
                        gameState->menuState->whichMenu = multiplayerMenu;
                        srand(((NetMessage *)packet->data)->payload);
                        gameState->bags = createBags();
                        spawnMinoNoDelete(gameState);
                        spawnGhostMinoNoDelete(gameState);
                        updatePreviewCol(gameState->previewCol, gameState->bags);
                        break;
                    case NET_BOARD_CHANNEL:
                        printf("Received board state update\n");
                        memcpy(gameState->boards->rightBoard->blocks, packet->data, packet->dataLength);
                        break;
                    default:
                        printf("Unknown channel: %d\n", event.channelID);
                }
                
                // process packet->data, packet->dataLength
                enet_packet_destroy(packet);
                break;
            }
        }
    }
}

void freeNetworkState(NetworkState *network) {
    enet_host_destroy(network->host);
    //free(network->hostUsername);
    //free(network->clientUsername);
    free(network);
}

void sendStart(GameState *gameState) {
    int rngSeed = time(NULL);
    NetworkState *network = gameState->networkState;
    gameState->menuState->whichMenu = multiplayerMenu;
    
    ENetPacket *packet = enet_packet_create(
        &(NetMessage){.type = MSG_START_GAME, .payload = rngSeed}, // payload can be RNG seed or other info
        sizeof(NetMessage),
        ENET_PACKET_FLAG_RELIABLE
    );

    enet_peer_send(network->peer, NET_MESSAGE_CHANNEL, packet);
    enet_host_flush(network->host);

    srand(rngSeed);
    gameState->bags = createBags();
    spawnMinoNoDelete(gameState);
    spawnGhostMinoNoDelete(gameState);
    updatePreviewCol(gameState->previewCol, gameState->bags);
}

void sendBoardState(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    if (network->peer == NULL) return;  // not connected yet
    
    Board *board = gameState->boards->leftBoard;
    int totalBlocks = board->xBlocks * board->yBlocks;

    Block *blocks = malloc(sizeof(Block) * totalBlocks);
    for(int x = 0; x < board->xBlocks; x++) {
        for(int y = 0; y < board->yBlocks; y++) {
            blocks[x + y * gameState->settings->GridWidth] = *getBlock(board, x, y);
            blocks[x + y * gameState->settings->GridWidth].rect.x += 800;
        }
    }
    
    ENetPacket *packet = enet_packet_create(
        blocks,
        sizeof(Block) * totalBlocks,
        ENET_PACKET_FLAG_RELIABLE
    );
    enet_peer_send(network->peer, NET_BOARD_CHANNEL, packet);
    enet_host_flush(network->host);  // actually send it now (not guaranteed by enet_peer_send alone)

    free(blocks);
}

void sendPreviewCol(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    if (network->peer == NULL) return;  // not connected yet
    
}

void lobbyChat(GameState *gameState) {

}