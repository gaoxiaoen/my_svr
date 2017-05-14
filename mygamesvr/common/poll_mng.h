#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <error.h>
#include <sys/socket.h>
#include "base_socket.h"

class CPollMng
{
public:
	CPollMng(int _buffer_size,int _max_epoll_size);
	~CPollMng();	

	void startpoll();
	void stoppoll();
	int addsocket(CBaseSocket *_base_socket);

private:
	int epoll_efd_;
	struct epoll_event *events_;
	int max_epoll_size;
	int epoll_run_;
	CBaseSocket* *epoll_sockets_[1000];
};