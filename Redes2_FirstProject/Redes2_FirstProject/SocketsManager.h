#pragma once

#include <list>

#include "SocketSelect.h"


class SocketsManager
{
public:
	typedef std::function<void(int,TcpSocket* socket)> OnSocketConnected;

	SocketsManager(OnSocketConnected onSocketConnected);
	~SocketsManager();

	void StartLoop();

	bool StartListener(unsigned short port);
	bool ConnectToServer(std::string ip, unsigned short port);

private:

	bool _isRunning = false;
	std::mutex _isRunningMutex;

	SocketSelect _selector;

	TcpListener* _listener;
	std::mutex _listenerMutex, playersIdMutex;
	int players;

	std::list<TcpSocket*> _sockets;
	std::mutex _socketsMutex;

	OnSocketConnected _OnSocketConnected;

	void SelectorLoop();
	void CheckListener();
	void CheckSockets();

	void AddSocket(TcpSocket* socket);
	void RemoveSocket(TcpSocket* socket);
	void RemoveSocketAsync(TcpSocket* socket);
};

