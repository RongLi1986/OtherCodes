#include<stdio.h>
#include<netinet/in.h>  
#include<sys/socket.h>  
#include<sys/types.h> 
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>
int main(int argc, char *argv[])
{
   struct sockaddr_in clientaddr; //define address
   pid_t pid;
   int clientfd,sendbytes,recvbytes; //client sockets
   struct hostent *host;
   char *buf,*buf_r; 
   if(argc < 4)
   {
    printf("usage:\n");
    printf("%s hostname port yourname\n",argv[0]);
    exit(1);
   }
   host = gethostbyname(argv[1]);
   if((clientfd = socket(AF_INET,SOCK_STREAM,0)) == -1)  //create the sockets
   {
     perror("socket error\n");
     exit(1);
   }
   
   clientaddr.sin_family = AF_INET;                        //bind the sockets
   clientaddr.sin_port = htons((uint16_t)atoi(argv[2]));
   clientaddr.sin_addr = *((struct in_addr *)host->h_addr);  
   bzero(&(clientaddr.sin_zero),0);

   if(connect(clientfd,(struct sockaddr *)&clientaddr,sizeof(struct sockaddr)) == -1) //connect
   {
     perror("connect error\n");
     exit(1);
   }
   
   //allocate the space for buffer
   buf=(char *)malloc(120);
   memset(buf,0,120);
   buf_r=(char *)malloc(100);

   if( recv(clientfd,buf,100,0) == -1)
   {
     perror("recv error");
     exit(1);
   }
   printf("\n%s\n",buf);

   pid = fork(); //create child process
   while(1)
   {
     if(pid > 0){   //parent process use for send message
   
       //get_cur_time(time_str);

       strcpy(buf,argv[3]);
       strcat(buf,":");
       memset(buf_r,0,100);
       //gets(buf_r);
       fgets(buf_r,100,stdin);
       strncat(buf,buf_r,strlen(buf_r)-1);
       //strcat(buf,time_str);
       //printf("---%s\n",buf);
       if((sendbytes = send(clientfd,buf,strlen(buf),0)) == -1)
       {
         perror("send\n");
         exit(1);
       }
     }
     else if(pid == 0)  // child process is use for recv message
     {
       memset(buf,0,100);
       if(recv(clientfd,buf,100,0) <= 0)
       {
         perror("recv error");
         close(clientfd);
         raise(SIGSTOP);
         exit(1);
       }
       printf("%s\n",buf);
     }
     else
       perror("fork error");
   }
   close(clientfd);
   return 0;    
}
