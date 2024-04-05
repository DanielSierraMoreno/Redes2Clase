#include "TcpSocket.h"

bool TcpSocket::Connect(std::string ip, unsigned short port)
{
	return connect(ip, port) == sf::Socket::Done;
}

void TcpSocket::Receive()
{
	Packet packet;
	sf::Socket::Status status = receive(packet); //Rebem el packet

	switch (status)
	{
	case sf::Socket::Done: //Si s'ha extret be el packet es procesa
		ProcessPacket(packet);
		break;
	case sf::Socket::Disconnected:
		_onSocketDisconnectMutex.lock(); //Si l'estat de rebre el packet es que el socket sha desconectat executem totes les lambdas de desconexio

		for (OnSocketDisconnect onDisconnect : _onSocketDisconnectList)
		{
			onDisconnect(this);
		}
		_onSocketDisconnectList.clear();

		_onSocketDisconnectMutex.lock();
		break;
	case sf::Socket::Partial:
	case sf::Socket::NotReady:
	case sf::Socket::Error:
	default:
		break;
	}
}

bool TcpSocket::Send(Packet::PacketKey key)
{
	Packet signedPacket;
	signedPacket << key;

	return send(signedPacket) == sf::Socket::Done; //Per enviar packet i retornem si sha pogut enviar be
}

bool TcpSocket::Send(Packet::PacketKey key, Packet packet)
{
	Packet signedPacket;
	signedPacket << key;

	signedPacket.append(packet.getData(), packet.getDataSize());
	return send(signedPacket) == sf::Socket::Done; //Per enviar packet i retornem si sha pogut enviar be
}

void TcpSocket::Subscribe(Packet::PacketKey key, OnReceivePacket onReceivePacket)
{
	_subscriptionsMutex.lock();
	_subscriptions[key] = onReceivePacket; //Afeix un relacio nova key-lambda al map o corregeix una que ja existia
	_subscriptionsMutex.unlock();
}

void TcpSocket::SubscribeAsync(Packet::PacketKey key, OnReceivePacket onReceivePacket)
{
	std::thread* subscribeThread = new std::thread(&TcpSocket::Subscribe, this, key, onReceivePacket);
	subscribeThread->detach();
}

void TcpSocket::SubscribeOnDisconnect(OnSocketDisconnect onSocketDisconect)
{
	_onSocketDisconnectMutex.lock();
	_onSocketDisconnectList.push_back(onSocketDisconect); //Afeix un lamda nova a les que s'executen al desconectar el socket

	_onSocketDisconnectMutex.unlock();

}

void TcpSocket::ProcessPacket(Packet packet)
{
	Packet::PacketKey key;
	packet >> key;

	std::map<Packet::PacketKey, OnReceivePacket>::iterator it;

	_subscriptionsMutex.lock();

	it = _subscriptions.find(key);
	if (it != _subscriptions.end())
	{
		it->second(packet); //Si trobem una key al map que te una lambda asociada la executem
	}

	_subscriptionsMutex.unlock();
}
