#include "websocket.h"

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/realtime/NRtTransportInterface.h>

#include "Containers/StringConv.h"
#include "WebSocketsModule.h"

DEFINE_LOG_CATEGORY_STATIC(NakamaWebsocket, Warning, Warning)

namespace Nakama {
namespace Unreal {

void UnrealWsTransport::connect(const std::string& url, NRtTransportType type)
{
	TransportType = type;
	WSConnection = FWebSocketsModule::Get().CreateWebSocket(UTF8_TO_TCHAR(url.c_str()));
	WSConnection->OnConnected().AddLambda([this]()
	{
		UE_LOG(NakamaWebsocket, Verbose, TEXT("Enqueue fireOnConnected"))
		EventsQueue.Enqueue(MakeTuple(CallbackDispatch::OnConnected, std::string(""), NRtClientDisconnectInfo{}));
	});
	WSConnection->OnConnectionError().AddLambda([this](const FString& Error)
	{
		UE_LOG(NakamaWebsocket, Verbose, TEXT("Enqueue fireOnError"))
		EventsQueue.Enqueue(MakeTuple(CallbackDispatch::OnError, std::string(FTCHARToUTF8(Error).Get()), NRtClientDisconnectInfo{}));
	});

	WSConnection->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		NRtClientDisconnectInfo info{
			static_cast<uint16_t>(StatusCode),
			FTCHARToUTF8(Reason).Get(),
			bWasClean
		};
		UE_LOG(NakamaWebsocket, Verbose, TEXT("Enqueue fireOnDisconnected"))
		EventsQueue.Enqueue(MakeTuple(CallbackDispatch::OnDisconnected, std::string(""), std::move(info)));
	});

	// Unreal's WebSocket implementation doesn't use frame opcode to distinguish between binary and text data
	// See: https://github.com/EpicGames/UnrealEngine/pull/7267
	// so let's do it ourselves. We don't have access to the opcode, so we use next best thing - expected message type
	if (TransportType == NRtTransportType::Text)
	{
		WSConnection->OnMessage().AddLambda([this](const FString& MessageString)
		{
			UE_LOG(NakamaWebsocket, Verbose, TEXT("Enqueue fireOnMessage"));
			FTCHARToUTF8 Convert(MessageString);
			EventsQueue.Enqueue(MakeTuple(CallbackDispatch::OnMessage, std::string(Convert.Get(), Convert.Length()), NRtClientDisconnectInfo{}));
		});
	} else
	{
		WSConnection->OnRawMessage().AddLambda([this](const void* Data , SIZE_T Size, SIZE_T  BytesRemaining)
		{
            MessageBuffer.Append(static_cast<const char*>(Data), Size);
            if (BytesRemaining == 0)
            {
                UE_LOG(NakamaWebsocket, Verbose, TEXT("Enqueue fireOnMessage"));
                EventsQueue.Enqueue(MakeTuple(CallbackDispatch::OnMessage, std::string(MessageBuffer.GetData(), MessageBuffer.Num()), NRtClientDisconnectInfo{}));
                MessageBuffer.Reset();
            }
		});
	}
	
	WSConnection->Connect();
}
	
void UnrealWsTransport::disconnect()
{
	// We don't want any more callbacks
	WSConnection->OnClosed().Clear();
	WSConnection->OnConnectionError().Clear();
	WSConnection->OnRawMessage().Clear();
	WSConnection->OnConnected().Clear();
	WSConnection->OnMessage().Clear();
	WSConnection->OnMessageSent().Clear();
	WSConnection->Close();
	_connected = false;
}
	
void UnrealWsTransport::tick()
{
	TTuple<CallbackDispatch, std::string, NRtClientDisconnectInfo> ev;
	while (EventsQueue.Dequeue(ev))
	{
		switch(ev.Get<0>())
		{
		case CallbackDispatch::OnConnected: fireOnConnected(); break;
		case CallbackDispatch::OnError: fireOnError(ev.Get<1>()); break;
		case CallbackDispatch::OnDisconnected: fireOnDisconnected(ev.Get<2>()); break;
		case CallbackDispatch::OnMessage: fireOnMessage(ev.Get<1>()); break;
		default: checkNoEntry(); 
		}
	}
}
	
bool UnrealWsTransport::send(const NBytes& buf)
{
	if (!_connected) return false;
	
	WSConnection->Send(buf.data(), buf.length(), TransportType == NRtTransportType::Binary);
	return true;
};

}
}
