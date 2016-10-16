#include "unp.h"

void replace (char*, char*, char*);
int main(int argc, char **argv){
	int sockfd, n , counter = 0;
	char recvline[MAXLINE +1];
	char msg[MAXLINE +1];
	struct sockaddr_in servaddr;

	if(argc != 3)
		err_quit("usage: a.out <IPaddress>");

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while(1){
		recvline[0] = '\0';
		while( (n = read(sockfd,recvline, MAXLINE)) > 0) {
			counter++;
			recvline[n] = 0;
	
			char *p;
			p = strstr(recvline,"QwErTy");
			char *e;
			e = strstr(recvline,"exit");
			if(e){
				exit(0);
			}
			if(p){
				printf("Incoming msg: %s\r\n",recvline);
				char code[6];
				snprintf(code,sizeof(code),"QwErTy");
				//replace(recvline,code,code);
				//printf("THE new msg :D : %s",recvline);	
				if(n < 0)
					err_sys("read error");
				msg[0] = '\0';
				printf("Enter your msg..\r\n");
				int errCode = scanf("%s", msg);
		
				if(errCode < 1){
					printf("Error received scanf %d", errCode);
				}
			
				if(strcmp(msg,"exit") == 0){
					char buff[MAXLINE];
	                                snprintf(buff, sizeof(buff), "exit");
        	                        Write(sockfd,buff,strlen(buff));
					exit(0);
				}
			
			
		
				char buff[MAXLINE];
				snprintf(buff, sizeof(buff), "%.24s\r\n", msg);
				Write(sockfd,buff,strlen(buff));
			}else{
				if(fputs(recvline,stdout) == EOF){
					err_sys("put error");
				}	
			}
		}
	}
}


void replace(char * o_string, char * s_string, char * r_string) {
      //a buffer variable to do all replace things
      char buffer[MAXLINE];
      //to store the pointer returned from strstr
      char * ch;
 
      //first exit condition
      if(!(ch = strstr(o_string, s_string)))
              return;
 
      //copy all the content to buffer before the first occurrence of the search string
      strncpy(buffer, o_string, ch-o_string);
 
      //prepare the buffer for appending by adding a null to the end of it
      buffer[ch-o_string] = 0;
 
      //append using sprintf function
      sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));
 
      //empty o_string for copying
      o_string[0] = 0;
      strcpy(o_string, buffer);
      //pass recursively to replace other occurrences
      return replace(o_string, s_string, r_string);
 }


/*char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}*/

