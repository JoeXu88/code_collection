#include <string>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

const uint32_t MAX_SIZE = 10240;

int main(int argc, char** argv)
{
    std::string server_host = "127.0.0.1";
    if(argc > 1)
    {
        server_host = argv[1];
    }

    int sock_fd;
	struct sockaddr_in server_addr;
	int port_number = 9099;
    if(argc > 2)
    {
        port_number = std::stoi(argv[2]);
    }

    printf("connet to sever: %s, port: %d\n", server_host.c_str(), port_number);

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr,"client Socket error:%s\n\a", strerror(errno));
        return -1;
	}

    struct hostent *ht = NULL;
    ht = gethostbyname(server_host.c_str());
    if(ht == NULL || ht->h_addr_list[0] == NULL)
    {
        printf("can not get host from %s", server_host.c_str());
        return -1;
    }

    char* addr = ht->h_addr_list[0];


    bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
    server_addr.sin_addr = *((struct in_addr*)addr);
    // inet_pton(AF_INET, server_host.c_str(), &server_addr.sin_addr);
	server_addr.sin_port = htons(port_number);

    int connect_ret = connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if(connect_ret < 0)
    {
        printf("can not connect to server: %s\n", server_host.c_str());
        return -1;
    }

    // char msg[MAX_SIZE] = {0};
    // memset(msg, '1', MAX_SIZE);

    int send_cnt = 2;
    std::string msg = "hello";
    int total = msg.length();
    int left = total;
	char buff[1024] = {0};
    while(send_cnt > 0)
    {
        while(left)
        {
            int n_sent = send(sock_fd, msg.c_str(), msg.length(), 0);
            left = total - n_sent;

        }
        left = total;
        
        // usleep(10000);
        --send_cnt;
        // if(send_cnt % 2 == 0)
        // {
            // int ret = recv(sock_fd, buff, sizeof(buff), 0);
        // }
        usleep(100000);
    }
    printf("send finish\n");

    while(send_cnt++ < 1000)
    {
        int ret = recv(sock_fd, buff, sizeof(buff), 0);
    }
    printf("read finish\n");
    while(true);
    close(sock_fd);

    return 0;
}