#ifndef NETWORK_H
#define NETWORK_H

typedef struct NetworkState NetworkState;
typedef struct GameState GameState;

typedef enum MessageType {
    MSG_HELLO,
    MSG_START_GAME
} MessageType;

typedef enum Player {
    server,
    client
} Player;

typedef struct NetMessage {
    MessageType type;
    int payload; // meaning depends on type — e.g. RNG seed for MSG_START_GAME
} NetMessage;

struct NetworkState {
    int connectSocket;
    int socket;
    char *hostUsername;
    char *clientUsername;
    Player player;
};



NetworkState *createNetworkState();
void createHost(NetworkState *networkState);
void createClient(NetworkState *networkState, char *ipString);
int setNonBlocking(int fd);
void closeSockets(NetworkState *network);
void freeNetworkState(NetworkState *network);

void sendStart(GameState *gameState);
void recieveStart(GameState *gameState);

void sendBoardState(GameState *gameState);
void recieveBoardState(GameState *gameState);

void lobbyChat(GameState *gameState);

#endif