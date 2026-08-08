#include <enet/enet.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "../include/network.h"
#include "../include/gameState.h"
#include "../include/tetrisLogic.h"
#include "../include/preview.h"
#include "../include/definitions.h"
#include "../include/block.h"
#include "../include/hold.h"


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

    networkState->host = enet_host_create(&address, 1, 1, 0, 0);
    if (networkState->host == NULL) {
        fprintf(stderr, "Failed to create ENet host\n");
        exit(1);
    }

    printf("Server listening on port 9000...\n");
}

void createClient(NetworkState *networkState, const char *ipString) {
    networkState->player = client;

    // Create a client host (NULL address means "pick any local address")
    networkState->host = enet_host_create(NULL, 1, 1, 0, 0);
    if (networkState->host == NULL) {
        fprintf(stderr, "Failed to create ENet host\n");
        exit(1);
    }

    ENetAddress address;
    enet_address_set_host(&address, ipString);
    address.port = 9000;

    // Connect to the server
    ENetPeer *peer = enet_host_connect(networkState->host, &address, 1, 0);
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

                NetMessage *message = (NetMessage *)packet->data;
                char *payload = (char *)packet->data + sizeof(NetMessage);
                size_t payloadSize = packet->dataLength - sizeof(NetMessage);
                
                switch(message->type) {
                    case MSG_START_GAME:
                        printf("Received NetMessage\n");
                        srand(*(int *)payload);
                        gameState->menuState->whichMenu = multiplayerMenu;
                        gameState->bags = createBags();
                        spawnMinoNoDelete(gameState);
                        spawnGhostMinoNoDelete(gameState);
                        updatePreviewCol(gameState->previewCol, gameState->bags);

                        sendPreviewCol(gameState);
                        sendHold(gameState);
                        break;
                    case MSG_BOARD_STATE:
                        printf("Received board state update\n");
                        memcpy(gameState->boards->rightBoard->blocks, payload, payloadSize);
                        break;
                    case MSG_PREVIEW_COL:
                        printf("Received preview column update\n");
                        memcpy(gameState->rightPreviewCol->previews, payload, payloadSize);
                        break;
                    case MSG_HOLD:
                        printf("Recieved hold update\n");
                        memcpy(gameState->rightHold, payload, payloadSize);
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
    uint32_t rngSeed = time(NULL);
    NetworkState *network = gameState->networkState;
    gameState->menuState->whichMenu = multiplayerMenu;

    size_t totalSize = sizeof(NetMessage) + sizeof(uint32_t);
    char* packet = malloc(totalSize);

    memcpy(packet + sizeof(NetMessage), &rngSeed, sizeof(uint32_t));
    
    NetMessage *header = (NetMessage *)packet;
    header->type = MSG_START_GAME;
    header->dataSize = sizeof(uint32_t);

    ENetPacket *enetPacket = enet_packet_create(
        packet,
        totalSize,
        ENET_PACKET_FLAG_RELIABLE
    );

    enet_peer_send(network->peer, NET_MESSAGE_CHANNEL, enetPacket);
    enet_host_flush(network->host);

    srand(rngSeed);
    gameState->bags = createBags();
    spawnMinoNoDelete(gameState);
    spawnGhostMinoNoDelete(gameState);
    updatePreviewCol(gameState->previewCol, gameState->bags);
    sendPreviewCol(gameState);

    free(packet);
}

void sendBoardState(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    if (network->peer == NULL) return;
    
    Board *board = gameState->boards->leftBoard;
    int totalBlocks = board->xBlocks * board->yBlocks;
    Block *blocks = malloc(sizeof(Block) * totalBlocks);
    for(int x = 0; x < board->xBlocks; x++) {
        for(int y = 0; y < board->yBlocks; y++) {
            blocks[x + y * gameState->settings->GridWidth] = *getBlock(board, x, y);
            blocks[x + y * gameState->settings->GridWidth].rect.x += 800;
        }
    }
    size_t boardDataSize = sizeof(Block) * totalBlocks;

    size_t totalSize = sizeof(NetMessage) + boardDataSize;
    char *packet = malloc(totalSize);
    memcpy(packet + sizeof(NetMessage), blocks, boardDataSize);

    NetMessage *header = (NetMessage *)packet;
    header->type = MSG_BOARD_STATE;
    header->dataSize = boardDataSize;

    ENetPacket *enetPacket = enet_packet_create(
        packet,
        totalSize,
        ENET_PACKET_FLAG_RELIABLE
    );

    enet_peer_send(network->peer, NET_MESSAGE_CHANNEL, enetPacket);
    enet_host_flush(network->host);

    free(blocks);
    free(packet);
}

void sendPreviewCol(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    if (network->peer == NULL) return;

    //Preview *previews = gameState->previewCol->previews;

    size_t previewSize = sizeof(Preview) * gameState->settings->PreviewMinoCount;
    size_t totalSize = sizeof(NetMessage) + previewSize;
    char *packet = malloc(totalSize); // char* instead of void* so it knows to shift forward totalSize in the memcpy line right after.
    // can also do void *packet, then in memcpy do: memcpy((char *)packet + ...)
    memcpy(packet + sizeof(NetMessage), gameState->previewCol->previews, previewSize);

    NetMessage *header = (NetMessage *)packet;
    header->type = MSG_PREVIEW_COL;
    header->dataSize = previewSize;

    ENetPacket *enetPacket = enet_packet_create(
        packet,
        totalSize,
        ENET_PACKET_FLAG_RELIABLE
    );
    
    enet_peer_send(network->peer, NET_MESSAGE_CHANNEL, enetPacket);
    enet_host_flush(network->host);

    free(packet);
}

void sendHold(GameState *gameState) {
    NetworkState *network = gameState->networkState;
    if (network->peer == NULL) return;

    size_t holdSize = sizeof(Hold);
    size_t totalSize = holdSize + sizeof(NetMessage);
    char *packet = malloc(totalSize);

    NetMessage *header = (NetMessage *)packet;
    header->type = MSG_HOLD;
    header->dataSize = holdSize;
    memcpy(packet + sizeof(NetMessage), gameState->hold, holdSize);

    ENetPacket *enetPacket = enet_packet_create(
        packet,
        totalSize,
        ENET_PACKET_FLAG_RELIABLE
    );

    enet_peer_send(network->peer, NET_MESSAGE_CHANNEL, enetPacket);
    enet_host_flush(network->host);

    free(packet);
}

void lobbyChat(GameState *gameState) {

}