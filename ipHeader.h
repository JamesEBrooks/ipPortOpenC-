#ifndef IPHEADER_H_INCLUDED
#define IPHEADER_H_INCLUDED

/// IP POrt start stuff

struct addrinfo {
    int     ai_flags;       // AI~_PASSIVE, AI_CANONNAME, etc.
    int     ai_family;      // AF_INET, AF_INET6, AF_UNSPEC
    int     ai_socktype;    // SOCK_STREAM, SOCK_DGRAM
    int     ai_protocol;    // use 0 for 'any
    size_t     ai_addrlen;     // size of ai_addr in bytes
    struct sockadder *ai_addr;  // struct sockaddr_in or _in6
    char    *ai_canonname;      // full canonical hostname

    struct addrinfo *ai_next;   // linked list, next node
};

/*
struct sockaddr {
    unsigned short  sa_family;
    char            sa_data[14];
};
*/
SOCKET s; //Socket handle

//CONNECTTOHOST – Connects to a remote host
bool ConnectToHost(int PortNo, char* IPAddress)
{
    //Start up Winsock…
    WSADATA wsadata;

    int error = WSAStartup(0x0202, &wsadata);

    //Did something happen?
    if (error)
        return false;

    //Did we get the right Winsock version?
    if (wsadata.wVersion != 0x0202)
    {
        WSACleanup(); //Clean up Winsock
        return false;
    }

    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (PortNo); //Port to connect on
    target.sin_addr.s_addr = inet_addr (IPAddress); //Target IP

    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        return false; //Couldn't create the socket
    }

    //Try connecting...

    if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
        return false; //Couldn't connect
    }
    else
        return true; //Success
}

//CLOSECONNECTION – shuts down the socket and closes any connection on it
void CloseConnection ()
{
    //Close the socket if it exists
    if (s)
        closesocket(s);

    WSACleanup(); //Clean up Winsock
}

#endif // IPHEADER_H_INCLUDED
