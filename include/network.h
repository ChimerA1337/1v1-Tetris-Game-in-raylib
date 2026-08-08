#ifndef NETWORK_H
#define NETWORK_H

#include <enet/enet.h>

typedef struct NetworkState NetworkState;
typedef struct GameState GameState;

typedef enum MessageType {
    MSG_HELLO,
    MSG_START_GAME,
    MSG_BOARD_STATE,
    MSG_PREVIEW_COL,
    MSG_HOLD
} MessageType;

typedef enum Player {
    server,
    client
} Player;

typedef struct NetMessage {
    uint8_t type;
    uint32_t dataSize;
} NetMessage;

struct NetworkState {
    ENetHost *host;           // your local endpoint
    ENetPeer *peer;           // connection to the other player (NULL if not connected yet)
    char *hostUsername;
    char *clientUsername;
    Player player;            // server or client
};

void initializeENet();
NetworkState *createNetworkState();
void createHost(NetworkState *networkState);
void createClient(NetworkState *networkState, const char *ipString);

void pollNetworkEvents(GameState *gameState);

void freeNetworkState(NetworkState *network);

void sendStart(GameState *gameState);
void sendBoardState(GameState *gameState);
void sendPreviewCol(GameState *gameState);
void sendHold(GameState *gameState);

void lobbyChat(GameState *gameState);

#endif