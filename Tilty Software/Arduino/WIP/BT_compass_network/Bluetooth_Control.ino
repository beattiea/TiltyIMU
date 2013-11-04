char* array[][2] = {slave1, slave2};

int connectToSlave(char* address) {
    
}

int parseCommandResponse(char* response) {
    
}


#define STATE "+STATE:" // Always starts a state command response
#define INITIALIZED "INITIALIZED"
#define READY "READY"
#define PAIRABLE "PAIRABLE"
#define PAIRED "PAIRED"
#define INQUIRING "INQUIRING"
#define CONNECTING "CONNECTING"
#define CONNECTED "CONNECTED"
#define DISCONNECTED "DISCONNECTED"
#define UNKNOWN "UNKNOWN"

// Bluetooth disconnect responses
#define DISC "+DISC:" // Always starts a disconnect command response
#define SUCCESS "SUCCESS"
#define LINK_LOSS "LINK_LOSS"
#define NO_SLC "NO_SLC"
#define TIMEOUT "TIMEOUT"
#define ERROR "ERROR"
