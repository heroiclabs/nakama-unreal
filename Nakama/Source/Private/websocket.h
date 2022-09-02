#pragma once

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/realtime/NRtTransportInterface.h>

#include "IWebSocket.h"

namespace Nakama {
namespace Unreal {

enum class CallbackDispatch {
    OnConnected,
    OnError,
    OnDisconnected,
    OnMessage,
};


    class UnrealWsTransport : public NRtTransportInterface
{
public:
	~UnrealWsTransport() override { disconnect(); }
	
   // These 2 are now absolette and should be removed from the interface
   void setActivityTimeout(uint32_t timeoutMs) override {};
   uint32_t getActivityTimeout() const override { return 0; };

   void tick() override;

   void connect(const std::string& url, NRtTransportType type) override;;

   /**
	* Close the connection with the server.
	*
	* Expectations from the implementation are:
	* - It is possible to call connect after disconnect on the same instance
	* - After disconnect returns any late messages arriving won't trigger messageCallback
	* - It MUST NOT trigger fireOn* synchronous in this call
	* - If connection is in progress and fireOnConnect is imminent, it MUST either schedule
	*   fireOnDisconnect to fire AFTER fireOnConnect or cancel it and fire neither.
	*
	*/
   void disconnect() override;

   bool send(const NBytes& data) override;
private:
	TSharedPtr<IWebSocket> WSConnection;
	NRtTransportType TransportType = NRtTransportType::Binary;
	// 0 indexed: fireOnConnected, fireOnerror, fireOnDisconnected, fireOnMessage
	TQueue<TTuple<CallbackDispatch, std::string, NRtClientDisconnectInfo>> EventsQueue;
    TArray<char> MessageBuffer;
};
}
}
