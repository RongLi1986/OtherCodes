#include<stdio.h>   
#include<stdlib.h>
#include<sys/types.h>  
#include<sys/stat.h>
#include<netinet/in.h>  
#include<sys/socket.h>  
#include<string.h>  
#include<unistd.h>
#include<signal.h>   //handle signal
#include<sys/ipc.h>
#include<errno.h>
#include<sys/shm.h>
#include<time.h>     //time 
#define PERM S_IRUSR|S_IWUSR  
#define MYPORT 4500  //port number
#define BACKLOG 10   //largest user number
#define WELCOME "|----------Welcome to the chat room! ----------|"  // show welcome information

// itoa: change the int to char*
void itoa(int i,char*string)
{
   int power,j;
   j=i;
   for(power=1;j>=10;j/=10)
     power*=10;
   for(;power>0;power/=10)
   {
     *string='0'+i/power;
     i%=power;
     string++;
   }
   *string='\0';
}

//get system time
void get_cur_time(char * time_str)
{
   time_t timep;
   struct tm *p_curtime;
   char *time_tmp;
   time_tmp=(char *)malloc(2);
   memset(time_tmp,0,2);

   memset(time_str,0,20);
   time(&timep);
   p_curtime = localtime(&timep);  //time.h
   strcat(time_str," (");
   itoa(p_curtime->tm_hour,time_tmp);
   strcat(time_str,time_tmp);
   strcat(time_str,":");
   itoa(p_curtime->tm_min,time_tmp);
   strcat(time_str,time_tmp);
   strcat(time_str,":");
   itoa(p_curtime->tm_sec,time_tmp);
   strcat(time_str,time_tmp);
   strcat(time_str,")");
   free(time_tmp);
}

//create shared memory
key_t shm_create()
{
   key_t shmid;
   if((shmid = shmget(IPC_PRIVATE,1024,S_IRUSR|S_IWUSR)) == -1)
   {
     fprintf(stderr,"Create Share Memory Error:%s\n\a",strerror(errno));
     exit(1);
   }
   return shmid;
}

int bindPort(unsigned short int port)     //create sockets and bind it into port
{  
   int sockfd;
   struct sockaddr_in my_addr;
   sockfd = socket(AF_INET,SOCK_STREAM,0);//create the stream sockets
   my_addr.sin_family = AF_INET;          //IPv4
   my_addr.sin_port = htons(port);        //convert port
   my_addr.sin_addr.s_addr = INADDR_ANY;
   bzero(&(my_addr.sin_zero),0);

   if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)) == -1)  //bind
   {
     perror("bind");
     exit(1);
   }
   printf("bind success!\n");
   return sockfd;
}


int main(int argc, char *argv[])
{
   int sockfd,clientfd,sin_size,recvbytes; 
   pid_t pid,ppid;  //for process
   char *buf, *r_addr, *w_addr, *temp, *time_str; //buffer
   struct sockaddr_in their_addr;  //structure for address
   key_t shmid;
   FILE *fp;             //for log file
   shmid = shm_create(); //create the shared memory

   temp = (char *)malloc(255);
   time_str=(char *)malloc(20);
   sockfd = bindPort(MYPORT); //return sockets
   if((fp=fopen("log.txt","w"))==NULL)  //create log file
   {
	   perror("create log fail");
	   exit(1);
   }
   while(1)
   {     
     if(listen(sockfd,BACKLOG) == -1) //listen
     {
       perror("listen error");
       exit(1);
     }
     printf("listening......\n");
     if((clientfd = accept(sockfd,(struct sockaddr*)&their_addr,&sin_size)) <0)//accept
     {
       perror("accept error");
       exit(1);
     }
     printf("accept from:%d\n",inet_ntoa(their_addr.sin_addr));
     send(clientfd,WELCOME,strlen(WELCOME),0);//send welcome
     buf = (char *)malloc(255);
    
     ppid = fork();//create process for every connect user
     if(ppid == 0)
     {
       pid = fork();  //create process for handle function
       while(1)
       {
         if(pid > 0)
         {
           //father process for recv message
           memset(buf,0,255);
  
           if((recvbytes = recv(clientfd,buf,255,0)) <= 0)
           {
             perror("recv1");
             close(clientfd);
             raise(SIGKILL);
             exit(1);
           }
           //here, we need write buf's data to share memory, thus it can send it to every client
           w_addr = shmat(shmid, 0, 0);
           memset(w_addr, '\0', 1024);
           strncpy(w_addr, buf, 1024);
           get_cur_time(time_str);
           strcat(buf,time_str);
		   fprintf(fp,"%s\n",buf);
           printf(" %s\n",buf);
         }
         else if(pid == 0)
         {
           //child process is used for send message from the shared memory
           sleep(1);
           r_addr = shmat(shmid, 0, 0);
         
           if(strcmp(temp,r_addr) != 0)
           {
             strcpy(temp,r_addr);
             get_cur_time(time_str);            
             strcat(r_addr,time_str);
             if(send(clientfd,r_addr,strlen(r_addr),0) == -1)
             {
               perror("send error");
             }
             memset(r_addr, '\0', 1024);
             strcpy(r_addr,temp);
           }
         }
         else
           perror("fork error");
       }
     }
   }
   //printf("------------------------------\n");
   free(buf);
   fclose(fp);
   close(sockfd);
   close(clientfd);
   return 0;
}
