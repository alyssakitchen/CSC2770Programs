#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define NTP_SERVER "44.31.46.123"
#define NTP_PORT 123
#define NTP_PACKET_SIZE 48
#define NTP_TIMESTAMP_DELTA 2208988800ull

typedef struct {
    uint8_t li_vn_mode;
    uint8_t stratum;
    uint8_t poll;
    uint8_t precision;
    uint32_t root_delay;
    uint32_t root_dispersion;
    uint32_t reference_id;
    uint32_t ref_ts_sec;
    uint32_t ref_ts_frac;
    uint32_t orig_ts_sec;
    uint32_t orig_ts_frac;
    uint32_t recv_ts_sec;
    uint32_t recv_ts_frac;
    uint32_t trans_ts_sec;
    uint32_t trans_ts_frac;
} ntp_packet;

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(){
    //FINDING THE LOCAL TIME
    time_t current_local_time;
    struct tm *local_time;
    char* localTime[33];

    // Get current time
    current_local_time = time(NULL);

    // Convert to local time
    local_time = localtime(&current_local_time);

    // Print local time
    printf("Local time: %s", asctime(local_time));

    //PRINTING THE NTP TIME
    int sockfd, n;
    struct sockaddr_in serv_addr;
    ntp_packet packet;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0)
        error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(NTP_PORT);
    if (inet_pton(AF_INET, NTP_SERVER, &serv_addr.sin_addr) <= 0)
        error("ERROR invalid address");

    memset(&packet, 0, sizeof(packet));
    packet.li_vn_mode = (0x03 << 6) | (0x03 << 3) | 0x03;

    if (sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR sending packet");

    n = recv(sockfd, &packet, sizeof(packet), 0);
    if (n < 0)
        error("ERROR receiving response");

    close(sockfd);

    time_t current_time = (ntohl(packet.trans_ts_sec) - NTP_TIMESTAMP_DELTA);
    printf("NTP time: %s", ctime(&current_time));

    //PRINTING THE DIFFERENCE
    double timeDifference = difftime(current_time, current_local_time);
    printf("Difference between local time and NTP time: %f seconds\n", timeDifference);

    return 0;
}