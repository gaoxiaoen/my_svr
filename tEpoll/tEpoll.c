#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>

#define MAXEVENTS 64

static int create_and_bind(char *port)
{
	struct addrinfo hints;
	struct addrinfo *result,*rp;
	int s,sfd;

	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	s = getaddrinfo(NULL,port,&hints,&result);
	if(s !=0 )
	{
		fprintf(stderr,"getaddrinfo :%s\n",gai_strerror(s));
		return -1;
	}
	for(rp=result;rp!=NULL;rp=rp->ai_next)
	{
		sfd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(sfd == -1)
			continue;
		s = bind(sfd,rp->ai_addr,rp->ai_addrlen);
		if(s==0)
			break;  //只需要链接一个地址即可
		close(sfd);
	}
	if(rp==NULL)
	{
		fprintf(stdree,"Could not bind.\n");
		return -1;
	}

	freeaddrinfo(result);

	return sfd;	
}

static int make_socket_non_blocking(int sfd)
{
	int flags,s;
	
	flags = fcntl(sfd,F_GETFL,0);
	if(flags == -1)
	{
		perror("fcntl is error");
		return -1;
	}

	flags |= O_NONBLOCK;
	s= fcntl(sfd,F_SETFL,flags);
	
	if (s==-1)
	{
		perror("tcntl set is error");
		return -1;
	}
	
	return 0;
}

//只能输入一个参数，就是端口
int main(int argc,char *argv[])
{
	int sfd,s;
	int efd;
	struct epoll_event event;
	struct epoll_event *events;
	
	sfd = create_and_bind(argv[1]);
	if(sfd == -1)
		abort();

	s = make_socket_non_blocking(sfd);
	if(s==-1)
		abort();
	
	s = listen(sfd,SOMAXCONN);  //设置最大的监听列表
	
	if(s==-1)
	{
		perror("listen error");
		abort();
	}
	
	efd = epoll_create1(0);
	if (efd == -1)
	{
		perror("epoll_create");
		abort();
	}

	event.data.fd = sfd;
	event.events = EPOLLIN|EPOLLOUT|EPOLLET; //读入，写出，边缘触发
	s = epoll_ctl(efd,EPOLL_CTL_ADD,sfd,&event);
	if(s== -1)
	{
		perror("epoll_ctl");
		abort();
	}
		
	events = calloc(MAXEVENTS,sizeof event);

	while(1)
	{
		int n,i;
		n = epoll_wait(efd,events,MAXEVENTS,-1);
		for(i=0;i<n;i++)
		{
			if((events[i].events&EPOLLERR)||
			   (events[i].events&EPOLLHUP))
			{
				fprintf(stderr,"epoll error!\n");
				close(events[i].data.fd);
				continue;
			}
			else if(sfd == events[i].data.fd)
			{
								
			}
		}		
	}

}































































































































