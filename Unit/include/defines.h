#ifndef WIFICONN
#define WIFICONN
#define WIFISSID "Connectify-Gothi"
#define WIFIPW  "gruppgothi"
#define WIFIHOST "192.168.137.101"
#define WIFIPORT 8888
#endif


#ifndef IR
typedef struct {
    int8_t values[4] ;
} irDir;

#define IR

#define irNorth 7
#define irEast 6
#define irSouth 5
#define irWest 4

#define recvNorth 3
#define recvEast 2
#define recvSouth 1
#define recvWest 0

#define WEST 0
#define EAST 1
#define SOUTH 2
#define NORTH 3

#endif