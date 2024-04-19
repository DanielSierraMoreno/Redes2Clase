#include "SocketsManager.h"
#include <iostream>

SocketsManager::SocketsManager(OnSocketConnected onSocketConnected)
{
	_OnSocketConnected = onSocketConnected;

}



SocketsManager::~SocketsManager()
{
	delete _listener;
	for (TcpSocket* socket : _sockets)
	{
		delete socket;
	}
}

void SocketsManager::StartLoop()
{
	_isRunningMutex.lock();

	if (_isRunning)
	{
		_isRunningMutex.unlock();
		return;
	}

	_isRunning = true;
	_isRunningMutex.unlock();

	std::thread* loopThread = new std::thread(&SocketsManager::SelectorLoop, this); //Comencem el bucle del selector perque vagi gestion els packets i conexions que es reben
	loopThread->detach();
}

bool SocketsManager::StartListener(unsigned short port)
{
	_listenerMutex.lock();

	if (_listener != nullptr)
	{
		_listenerMutex.unlock();
		return false;
	}

	_listener = new TcpListener(); //Inicialitzem el listener per poder començar a escoltar conexions
	if (!_listener->Listen(port))
	{
		delete _listener;
		_listenerMutex.unlock();
		return false;
	}

	_selector.Add(*_listener); //Afegim el listener al selector pq gestioni les coneixon request

	_listenerMutex.unlock(); 

	return true;
}

bool SocketsManager::ConnectToServer(std::string ip, unsigned short port)
{
	TcpSocket* socket = new TcpSocket(); //Creem un socket per conectarnos

	if (!socket->Connect(ip, port))  //Intentem conectarnos a la ip
	{
		delete socket;
		return false;
	}

	AddSocket(socket); //Si el podem conectar l'afegim a a llista de sockets que te el selector

	return true; //false
}

void SocketsManager::SelectorLoop() //Bucle que revisa el selector
{
	_isRunningMutex.lock();
	bool isRunning = true;
	_isRunningMutex.unlock();


	while (isRunning)
	{
		if (_selector.Wait()) //Si el selector te algun TcpSocket o TcpListener amb un informacio a rebre
		{
			std::cout << "In Selector" << std::endl;

			CheckListener(); //Revisar si es el listener qui ha de rebre info

			CheckSockets(); //Revisar si es algun dels sockets qui ha de rebre info

		}
		_isRunningMutex.lock();
		 isRunning = _isRunning;
		_isRunningMutex.unlock();
	}

}

void SocketsManager::CheckListener()
{
	_listenerMutex.lock();

	if (_listener != nullptr && _selector.IsReady(*_listener))
	{
		TcpSocket* socket = new TcpSocket(); 
		if (_listener->Accept(*socket)) //Si el listener te una conexio pendent se li fa un TcpSocket y es guarda dins la llista de TCpSockets
		{
			AddSocket(socket);
		}
		else
		{
			delete socket;
		}
	}

	_listenerMutex.unlock();

}

void SocketsManager::CheckSockets()
{
	_socketsMutex.lock();

	for (TcpSocket* socket : _sockets)
	{
		if (_selector.IsReady(*socket)) //Es revisa quin es el socket que ha de rebre un packet
		{
			socket->Receive();
		}
	}
	_socketsMutex.unlock();

}

void SocketsManager::AddSocket(TcpSocket* socket)
{
	_socketsMutex.lock();

	playersIdMutex.lock();
	int newPlayerId = players;
	players++;
	playersIdMutex.unlock();

	_sockets.push_back(socket); //S'afegeix el TCPSocket a la llista de TCPSocket
	_selector.Add(*socket); //S'afegeix el TCPSocket a la llista interna que te SocketSelect

	_OnSocketConnected(newPlayerId,socket); //S'executa la lambda que hem guardat al cosntrcutor passant el nou socket conectat

	socket->SubscribeOnDisconnect([this](TcpSocket* socket) { //S'afegeix una lamda mes a la llista de lambdas que s'executen al desoncetar el TCPSocket
		RemoveSocketAsync(socket);
	});


	_socketsMutex.unlock();
}

void SocketsManager::RemoveSocket(TcpSocket* socket)
{

	_selector.Remove(*socket); //Treiem el socket del selector pq ya no hem de revisar si rep mes packets


	_socketsMutex.lock();

	_sockets.remove(socket); //Treiem el socket de la llista pq ya no rebra mes packets

	_socketsMutex.unlock();
	delete socket;
}

void SocketsManager::RemoveSocketAsync(TcpSocket* socket)
{
	std::thread* removeSocketThread = new std::thread(&SocketsManager::RemoveSocket, this, socket);
	removeSocketThread->detach();
}
