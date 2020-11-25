// // /*./client serv_ip serv_port*/
// #include"net.h"

// void usage(char *s)
// {
//     printf("\n%s serv_ip serv_port",s);
//     printf("\n\t serv_ip: server ip address");
//     printf("\n\t serv_port: server port(>5000)\n\n");
// }

// int main(int argc,char **argv)
// {
//     int fd = -1;

//     int port = -1;

// 	struct sockaddr_in sin;

//     if(argc != 3){
//         usage(argv[0]);
//         exit(1);
//     }
	
// 	/*1.创建socket fd*/ 
// 	if( (fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
// 		perror("socket");
// 		exit(1);
// 	}

//     port = atoi(argv[2]);
//     if(port < 5000){
//         usage(argv[0]);
//         exit(1);
//     }

//     /*2.连接服务器*/
//     /*2.1填充struct sockaddr_in结构体变量*/
// 	bzero(&sin,sizeof(sin)); 
// 	sin.sin_family = AF_INET;
// 	sin.sin_port = htons(port);//网络字节序的端口号
	
// #if 0
// 	sin.sin_addr.s_addr = inet_addr(SERV_IP_ADDR); 
// #else
// 	if( (inet_pton(AF_INET,argv[2],(void *)&sin.sin_addr.s_addr)) != 1){
// 		perror("inet_pton");
// 		exit(1);
// 	}
// #endif

//     if(connect(fd,(struct sockaddr *)&sin,sizeof(sin)) < 0){
//         perror("bind");
// 		exit(1);
//     }

// 	printf("Client starting......OK!\n");

//     /*3.读写数据*/
//     //char buf[BUFSIZ];
//     char recbuf[BUFSIZ],sendbuf[BUFSIZ];
//     // while(1){
//     //     bzero(buf,BUFSIZ);
//     //     if(fgets(buf,BUFSIZ-1,stdin) == NULL){
//     //         continue;
//     //     }
//     //     write(fd,buf,strlen(buf));
//     //     if(	!strncasecmp(buf,QUIT_STR,strlen(QUIT_STR))){	//用户输入了quit字符
// 	// 		printf("Client is exiting!\n");
// 	// 		break;
// 	// 	}
//     // }

//     while(1){
//                 bzero(recbuf,BUFSIZ);
//                 bzero(sendbuf,BUFSIZ);
//                 memset(sendbuf,0,sizeof(sendbuf));
//                 memset(recbuf,0,sizeof(recbuf));
                
//                 printf("\n请输入要查询的房间号(1-20)\n");
//                 fgets(sendbuf,sizeof(sendbuf),stdin);
//                 send(fd,sendbuf,strlen(sendbuf),0);
                
//                 printf("查询结果(0.00为未采集):");
//                 recv(fd,recbuf,sizeof(recbuf),0);
		
//                 fputs(recbuf,stdout);

//         }

//     /*4.关闭套接字*/
//     close(fd);
//     return 0;
// }


#include"net.h"

int main()
{
	int sockfd;
	char ipstr[] = "127.0.0.1";
	char recbuf[1024],sendbuf[1024];
	struct sockaddr_in sfdaddr;	

	sockfd  = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		perror("sockfd");
		exit(1);
	}
	bzero(&sfdaddr,sizeof(sfdaddr));
	sfdaddr.sin_family = AF_INET;
	sfdaddr.sin_port = htons(5678);
	inet_pton(AF_INET,ipstr,&sfdaddr.sin_addr.s_addr );
	connect(sockfd,(struct sockaddr *)&sfdaddr,sizeof(sfdaddr));
	while(1){
                memset(sendbuf,0,sizeof(sendbuf));
                memset(recbuf,0,sizeof(recbuf));
                
                printf("\n输入查询地点\n");
                fgets(sendbuf,sizeof(sendbuf),stdin);
                send(sockfd,sendbuf,strlen(sendbuf),0);
                
                printf("数据查询结果:");
                recv(sockfd,recbuf,sizeof(recbuf),0);
		
                fputs(recbuf,stdout);

        }

	close(sockfd);
	return 0;
}