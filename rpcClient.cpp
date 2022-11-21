// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/socket.h>
#include<cstring>
// #include<sys/types.h>
// #include<netinet/in.h>
// #include<sys/time.h>
// #include<sys/wait.h>
// #include<string.h>
#include<unistd.h>
#include<arpa/inet.h> 

#include<bits/stdc++.h>


using namespace std ;

struct obj{
       int l ,b , h ;
	
};
void pack(int l , int b, int h , obj&p){
	p.l = l ;
	p.b= b;
	p.h = h;
}

int main() {
	int c_sock;
	c_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	

	if(connect(c_sock, (struct sockaddr*)&client, sizeof(client)) == -1) {
	printf("Connection failed");
	return 0;
	}
    int len , bre , hei ;
	cout<<"Enter the lenght , breadth , height :";
	cin>>len>>bre>>hei ;
	obj p ;
    pack(len ,bre ,hei , p);
	cout<<"Parameters packed at client stub...\n";
	
	
    send(c_sock , &p , sizeof(p) , 0);
	cout<<"Sending the data to server...\n";
	
// receiving the answer
    int check  ;
    recv(c_sock , &check , sizeof(check) , 0);
	cout<<"Result received....\n";

	cout<<"Volume of cuboid is :"<<check<<endl;
	close(c_sock);
	return 0;
}