#pragma once

#include "nakama-cpp/URLParts.h"

namespace Nakama {

// Result of async operation
enum class NetIOAsyncResult {
    ERR = -1,  // error, no further progress possible
    AGAIN = 0,   // to be called again
    DONE = 1,    // successful completion
};

class WslayIOInterface {
public:
    virtual ~WslayIOInterface() {}
    virtual int recv(void* buf, size_t len, int* wouldBlock) = 0;
    virtual int send(const void* data, size_t len, int* wouldBlock) = 0;
    virtual void close() = 0;
    virtual NetIOAsyncResult connect_init(const URLParts& urlParts) = 0;
    virtual NetIOAsyncResult connect_tick() = 0;
};

}