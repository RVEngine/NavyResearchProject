#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <ClientToSocket2.h>
#include<sstream> 
// TCP socket type
#define DEFAULT_PROTO SOCK_STREAM




//void Usage(char* progname)
//{
//    fprintf(stderr, "Usage: %s -p [protocol] -n [server name/IP] -e [port_num] -l [iterations]\n", progname);
//    fprintf(stderr, "Where:\n\tprotocol is one of TCP or UDP\n");
//    fprintf(stderr, "\t- server is the IP address or name of server\n");
//    fprintf(stderr, "\t- port_num is the port to listen on\n");
//    fprintf(stderr, "\t- iterations is the number of loops to execute.\n");
//    fprintf(stderr, "\t- (-l by itself makes client run in an infinite loop,\n");
//    fprintf(stderr, "\t- Hit Ctrl-C to terminate it)\n");
//    fprintf(stderr, "\t- The defaults are TCP , localhost and 2007\n");
//    WSACleanup();
//    exit(1);
//}


SOCKET  conn_socket;
int retval;
void ClientToSocket2::Connect()
{
    
    //char Buffer[256];
    // default to localhost
    char* server_name = "localhost";
    unsigned short port = 10000;
    //int loopflag = 1;
    //int loopcount, maxloop = 1;
    unsigned int addr;
    int socket_type = DEFAULT_PROTO;
    struct sockaddr_in server;
    struct hostent* hp;
    WSADATA wsaData;
    socket_type = SOCK_STREAM;

               /* case 'l':
                    loopflag = 1;
                    if (argv[i + 1]) {
                        if (argv[i + 1][0] != '-')
                            maxloop = atoi(argv[i + 1]);
                    }
                    else
                        maxloop = -1;*/
                   
 

    if((retval = WSAStartup(0x202, &wsaData)) != 0)
    {
        OutputDebugString("Client: WSAStartup() failed with error %d\n" + retval);
        WSACleanup();
        exit(1);
    }
    else
        printf("Client: WSAStartup() is OK.\n");


    // Attempt to detect if we should call gethostbyname() or gethostbyaddr()
    if (isalpha(server_name[0]))
    {   // server address is a name
        hp = gethostbyname(server_name);
    }
    else
    { // Convert nnn.nnn address to a usable one
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
    }
    if (hp == NULL)
    {
        OutputDebugString("Client: Cannot resolve address \"%s\": Error %d\n  localhost " + WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    else
        OutputDebugString("Client: gethostbyaddr() is OK.\n");

    // Copy the resolved information into the sockaddr_in structure
    memset(&server, 0, sizeof(server));
    memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(port);

    conn_socket = socket(AF_INET, socket_type, 0); /* Open a socket */
    if (conn_socket < 0)
    {
        OutputDebugString("Client: Error Opening socket: Error %d\n" + WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    else
        OutputDebugString("Client: socket() is OK.\n");

    // Notice that nothing in this code is specific to whether we
    // are using UDP or TCP.
    // We achieve this by using a simple trick.
    //    When connect() is called on a datagram socket, it does not
    //    actually establish the connection as a stream (TCP) socket
    //    would. Instead, TCP/IP establishes the remote half of the
    //    (LocalIPAddress, LocalPort, RemoteIP, RemotePort) mapping.
    //    This enables us to use send() and recv() on datagram sockets,
    //    instead of recvfrom() and sendto()

    OutputDebugString("Client: Client connected\n");
    if (connect(conn_socket, (struct sockaddr*) & server, sizeof(server)) == SOCKET_ERROR)
    {
        OutputDebugString("Client: connect() failed: %d\n" + WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    else
        OutputDebugString("Client: connect() is OK.\n");

    // Test sending some string
    //loopcount = 1;
    //do
    //{
    //    wsprintf(Buffer, text.c_str());
    //    retval = send(conn_socket, Buffer, (int)strlen(Buffer), 0);
    //    if (retval == SOCKET_ERROR)
    //    {
    //        OutputDebugString("Client: send() failed: error %d.\n" + WSAGetLastError());
    //        WSACleanup();
    //        exit(1);
    //    }
    //    else
    //        OutputDebugString("Client: send() is OK.\n");


    //    retval = recv(conn_socket, Buffer, (int)strlen(Buffer), 0);
    //    if (retval == SOCKET_ERROR)
    //    {
    //        OutputDebugString("Client: recv() failed: error %d.\n" + WSAGetLastError());
    //        closesocket(conn_socket);
    //        WSACleanup();
    //        exit(1);
    //    }
    //    else
    //        OutputDebugString("Client: recv() is OK.\n");

    //    // We are not likely to see this with UDP, since there is no
    //    // 'connection' established.
    //    if (retval == 0)
    //    {
    //        OutputDebugString("Client: Server closed connection.\n");
    //        closesocket(conn_socket);
    //        WSACleanup();
    //        exit(1);
    //    }
    //   /* std::string recieved;
    //    std::stringstream recievedStream;
    //    recievedStream << Buffer;
    //    recievedStream >> recieved;*/
    //    char* output = ("Client: Received %d bytes, data \"%s\" from server.\n", retval, Buffer);
    //    OutputDebugString(output);

    //    if (!loopflag)
    //    {
    //        OutputDebugString("Client: Terminating connection...\n");
    //        break;
    //    }
    //    else
    //    {
    //        if ((loopcount >= maxloop) && (maxloop > 0))
    //            break;
    //    }
    //    loopcount--;
    //}while (loopcount >= maxloop);
    //closesocket(conn_socket);
    //WSACleanup();

}


void ClientToSocket2::sendMessage(std::string text)
{
    char Buffer[256];
    wsprintf(Buffer, text.c_str());
    retval = send(conn_socket, Buffer, (int)strlen(Buffer)+1, 0);
    if (retval == SOCKET_ERROR)
    {
        OutputDebugString("Client: send() failed: error %d.\n" + WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    else
        OutputDebugString("Client: send() is OK.\n");
}
void ClientToSocket2::recieveMessage()
{
    char Buffer[256];
    retval = recv(conn_socket, Buffer, (int)strlen(Buffer)-1, 0);
    if (retval == SOCKET_ERROR)
    {
        OutputDebugString("Client: recv() failed: error %d.\n" + WSAGetLastError());
        closesocket(conn_socket);
        WSACleanup();
        exit(1);
    }
    else
        OutputDebugString("Client: recv() is OK.\n");
    
    char* output = ("Client: Received %d bytes, data \"%s\" from server.\n", retval, Buffer);
    OutputDebugString(output);
}

void ClientToSocket2::Disconnect()
{
  closesocket(conn_socket);
  WSACleanup();
}
