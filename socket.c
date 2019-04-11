#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

// #define PORT     8080

typedef struct {

  uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
                           // li.   Two bits.   Leap indicator.
                           // vn.   Three bits. Version number of the protocol.
                           // mode. Three bits. Client will pick mode 3 for client.

  uint8_t stratum;         // Eight bits. Stratum level of the local clock.
  uint8_t poll;            // Eight bits. Maximum interval between successive messages.
  uint8_t precision;       // Eight bits. Precision of the local clock.

  uint32_t rootDelay;      // 32 bits. Total round trip delay time.
  uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
  uint32_t refId;          // 32 bits. Reference clock identifier.

  uint32_t refTm_s;        // 32 bits. Reference time-stamp seconds.
  uint32_t refTm_f;        // 32 bits. Reference time-stamp fraction of a second.

  uint32_t origTm_s;       // 32 bits. Originate time-stamp seconds.
  uint32_t origTm_f;       // 32 bits. Originate time-stamp fraction of a second.

  uint32_t rxTm_s;         // 32 bits. Received time-stamp seconds.
  uint32_t rxTm_f;         // 32 bits. Received time-stamp fraction of a second.

  uint32_t txTm_s;         // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
  uint32_t txTm_f;         // 32 bits. Transmit time-stamp fraction of a second.

} ntp_packet;              // Total: 384 bits or 48 bytes.


void error(const char *error) {
    printf("%s", error);
}

int main(int argc, char ** arg) {

	// Create and zero out the packet. All 48 bytes worth.

	ntp_packet packet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	memset( &packet, 0, sizeof( ntp_packet ) );

	// Set the first byte's bits to 00,011,011 for li = 0, vn = 3, and mode = 3. The rest will be left set to zero.

	*( ( char * ) &packet + 0 ) = 0x1b; // Represents 27 in base 10 or 00011011 in base 2.


	// Create a UDP socket, convert the host-name to an IP address, set the port number,
	// connect to the server, send the packet, and then read in the return packet.

	struct sockaddr_in serv_addr; // Server address data structure.
	struct hostent *server;      // Server data structure.
	int sockfd;
	char host_name[] = "google.com"; 
	int port = 8080;

	sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // Create a UDP socket.

	if ( sockfd < 0 )
	error( "ERROR opening socket" );

	server = gethostbyname( host_name ); // Convert URL to IP.

	if ( server == NULL )
	error( "ERROR, no such host" );

	// Zero out the server address structure.

	bzero( ( char* ) &serv_addr, sizeof( serv_addr ) );

	serv_addr.sin_family = AF_INET;

	// Copy the server's IP address to the server address structure.

	bcopy( ( char* )server->h_addr, ( char* ) &serv_addr.sin_addr.s_addr, server->h_length );

	// Convert the port number integer to network big-endian style and save it to the server address structure.

	serv_addr.sin_port = htons( port );

	return 0;
}
