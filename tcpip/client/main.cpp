
#include "Client.h"

int main()
{
    auto client = new Client();
    client->openConnection();
    client->write("12345678901234567890123456");


//    struct sockaddr_in peer;
//    int s;
//    ssize_t rc;
//    char buf[1];
//
//    peer.sin_family = AF_INET;
//    peer.sin_port = htons(7500);
//    peer.sin_addr.s_addr = inet_addr("127.0.0.1");
//
//    s = socket(AF_INET, SOCK_STREAM, 0);
//
//    connect(s, (struct sockaddr *)&peer, sizeof(peer));
//
//    rc = send(s, "12345678901234567890123456", 26, 0);
//
//    rc = recv(s, buf, 1, 0);
//
//    if (rc <= 0)
//        perror("recv call failed");
//    else
//        printf("%c\n", buf[0]);
//
//    shutdown(s, SHUT_RDWR);
//    close(s);
//
//    send(s, "12345678901234567890123456", 1, 0);

    return 0;
}
