#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <zconf.h>
#include <mutex>
#include <vector>
#include <algorithm>

#define NUMBER_OF_READN_SYMBOLS 5
#define NUMBER_OF_CLIENTS 5
#define PORT 7500

std::mutex mtx;

std::vector<int> arrayOfConnection;

typedef struct {
    int accept_socket;
    int client_sockets [NUMBER_OF_CLIENTS];
    char action;
} pthrData;

int read_n( int n, int s1, char* result )
{
    char buf [1];
    int number_of_entered = 0;
    ssize_t rc = -1;

    while ( number_of_entered != n ) {
        rc = recv( s1, buf, 1, 0 );
        if ( rc == -1 ) {
            break;
        }
        result[number_of_entered] = buf[0];
        number_of_entered += rc;
    }
    return (int)rc;
}

void* threadFunc( void* threadData )
{
    auto data = ( int* ) threadData;
    int s1 = *data;
    char result [NUMBER_OF_READN_SYMBOLS];
    int rc = -1;

    while ( true ) {
        rc = read_n( NUMBER_OF_READN_SYMBOLS, s1, result );
        if (rc == -1) {
            break;
        }
        std::string res(result);
        if (res.empty()) {
            printf("result is null\n");
        } else {
            printf( "%d : %s\n", s1, result );
        }
    }

    mtx.lock();
    arrayOfConnection.erase( std::remove(arrayOfConnection.begin(), arrayOfConnection.end(), s1), arrayOfConnection.end() );
    mtx.unlock();

    pthread_exit(0);
}

void* acceptThread( void* threadData )
{
    auto data = ( pthrData* ) threadData;
    int client_socket;

    while ( true ) {
        if ( data->action == 'e' ) {
            break;
        }
        if ( arrayOfConnection.size() < NUMBER_OF_CLIENTS) {
            client_socket = accept( data->accept_socket, nullptr, nullptr );
            if ( client_socket < 0 ) {
                break;
            }
            pthread_t thread;
            pthread_create( &thread, nullptr, threadFunc, &client_socket );

            mtx.lock();
            arrayOfConnection.push_back( client_socket );
            mtx.unlock();
        }
    }

    for ( int i = 0; i < arrayOfConnection.size(); i++ ) {
        shutdown( arrayOfConnection[i], SHUT_RDWR );
        close( arrayOfConnection[i] );
    }

    pthread_exit(0);
}

int main()
{
    struct sockaddr_in local;

    local.sin_family = AF_INET;
    local.sin_port = htons( PORT );
    local.sin_addr.s_addr = htonl( INADDR_ANY );

    auto threadData = ( pthrData* ) malloc( sizeof( pthrData ) );

    threadData->accept_socket = socket( AF_INET, SOCK_STREAM, 0 );
    bind( threadData->accept_socket, ( struct sockaddr * ) &local, sizeof( local ) );
    listen( threadData->accept_socket, 5 );

    auto thread = ( pthread_t* ) malloc( sizeof( pthread_t ) );
    pthread_create( thread, nullptr, acceptThread, threadData );

    while ( true ) {
        threadData->action = ( char ) getchar();

        if ( threadData->action == 'i' ) {
            printf( "info\n" );
            printf( "Number of connections: %d\n", (int) arrayOfConnection.size() );
            for (int i = 0; i < arrayOfConnection.size(); i++) {
                printf( "%d. client socket: %d\n", i + 1, arrayOfConnection[i] );
            }
        } else if ( threadData->action == 'e' ) {
            printf( "exit\n" );
            break;
        } else if ( threadData->action == 'h' ) {
            printf( "i -- info\n"
                    "e -- exit\n" );
        } else if ( threadData->action == 'c' ) {
            printf( "close connection: enter number of client\n" );
            int client_number = -1;
            scanf("%d", &client_number);

            printf("client_number  %d\n", client_number-1);

            shutdown( arrayOfConnection[client_number-1], SHUT_RDWR );
            close( arrayOfConnection[client_number-1] );

            printf( "socket %d closed \n", arrayOfConnection[client_number-1] );
        }
    }

    shutdown( threadData->accept_socket, SHUT_RDWR );
    close( threadData->accept_socket );

    pthread_join( *thread, NULL );

    free( thread );
    free( threadData );

    exit( 0 );
}
