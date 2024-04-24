#include<stdio.h>
#include<stdlib.h>	
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/udp.h>


#define SIZE 1024
#define PORT 4440



void calculateHammingCode(char* data, int dataSize, char* result) {
    
    int r = 0;
    while ((1 << r) < (dataSize + r + 1)) {
        r++;
    }

    
    int dataBits = dataSize + r;
    int hammingCode[dataBits];
    memset(hammingCode, 0, sizeof(hammingCode));

    int j = 0;
    for (int i = 0; i < dataBits; i++) {
        if (!((i + 1) & i)) { 
            continue;
        }
        hammingCode[i] = data[j] - '0';
        j++;
    }

  
    for (int i = 0; i < r; i++) {
        int parity = 0;
        for (int j = (1 << i); j <= dataBits; j += (1 << (i + 1))) {
            for (int k = j; k <= dataBits && k < j + (1 << i); k++) {
                parity ^= hammingCode[k - 1];
            }
        }
        hammingCode[(1 << i) - 1] = parity;
    }

  
    for (int i = 0; i < dataBits; i++) {
        result[i] = hammingCode[i] + '0';
    }
    result[dataBits] = '\0';
}

int main(){

int sockfd=socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in addr;
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=inet_addr("127.0.0.1");
addr.sin_port=htons(PORT);
socklen_t addrlen=sizeof(addr);
bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
char buffer[SIZE];
recvfrom(sockfd,buffer,SIZE,0,(struct sockaddr*)&addr,&addrlen);
printf("Data recived: %s\n",buffer);

char hammingCode[SIZE];
calculateHammingCode(buffer, strlen(buffer), hammingCode);
printf("Hamming code : %s\n",hammingCode);
sendto(sockfd,hammingCode,SIZE,0,(struct sockaddr*)&addr,sizeof(addr));


return 0;
}

