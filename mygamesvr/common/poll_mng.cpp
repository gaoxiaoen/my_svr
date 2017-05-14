#include "poll_mng.h"

CPollMng::CPollMng(int _buffer_size,int _max_epoll_size)
{
	max_epoll_size_ = _max_epoll_size;
	epoll_run_ = 1;
	epoll_efd_ = epoll_create1(0);
	if(epoll_efd_ == -1)
	{
		perror("epoll_create");
		abort();
	}

	events_ = calloc(_max_epoll_size,sizeof(struct epoll_even));

	for (int i = 0; i < _max_epoll_size; ++i)
	{
		// 分配内存空间
	}
}

CPollMng::~CPollMng()
{
	for (int i = 0; i < max_epoll_size_; ++i)
	{
		if(epoll_sockets_[i]!=NULL)
		{
			//TODO:销毁占用的内存空间
		}
	}

	free(events_);
	close(epoll_efd_);
}

CPollMng::addsocket(CBaseSocket *_base_socket)
{
	int socketfd = _base_socket->get_socket_fd();
	int events = _base_socket->get_socket_event();
	if (epoll_sockets_[socketfd] == NULL)
	{
		epoll_sockets_[socketfd] = _base_socket;
		struct epoll_event event;
		event.data.fd = socketfd;
		event.events =events;
		int res = epoll_ctl(epoll_efd_,EPOLL_CTL_ADD,socketfd,&event);
		if (res == -1)
		{
			perror("epoll_ctl");
			abort();
		}
	}
}

CPollMng::startpoll()
{
	while(epoll_run_)
	{
		int strrigle = epoll_wait(epoll_efd_,events_,max_epoll_size_,-1);
		for (int i = 0; i < strrigle; ++i)
		{
			struct epoll_event event;
			event = events_ + i;
			int socketfd = event.data.fd;
			if (epoll_sockets_[socketfd] == NULL)
			{
				continue;
			}
			if ((event.events&EPOLLERR)||
				(event.events&EPOLLHUP))
			{
				//关闭连接
			}
			elseif(event&EPOLLOUT)
			{
				//有输出连接
			}
			elseif(event&EPOLLIN)
			{
				//TODO:需要分情况讨论是否有新连接或者关闭连接，或者是有消息进入
			}
		}
	}
}