#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

#define NUMER_OF_SYMOBLS 5

char* readn( int n, int s, int s1)
{
    char buf[n];
    int number_of_entered = 0;

    while (number_of_entered != n) {
        s1 = accept(s, NULL, NULL);

    }


    return buf;
}

int main( void )
{
    struct sockaddr_in local;
    int s;
    int s1;
    int rc;
    char buf[ 1 ];

    local.sin_family = AF_INET;
    local.sin_port = htons( 7500 );
    local.sin_addr.s_addr = htonl( INADDR_ANY );

    s = socket( AF_INET, SOCK_STREAM, 0 );

    rc = bind( s, ( struct sockaddr * )&local, sizeof( local ) );

    rc = listen( s, 5 );

    s1 = accept(s, NULL, NULL);

    readn(NUMER_OF_SYMOBLS, s, s1);

    rc = recv( s1, buf, 1, 0 );

    printf( "%c\n", buf[ 0 ] );

    rc = send( s1, "2", 1, 0 );

    shutdown(s, SHUT_RDWR);

    close(s);

    exit( 0 );
}
