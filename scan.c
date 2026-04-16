#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

const char *get_service(int port) {
    switch (port) {
        case 21: return "FTP";
        case 22: return "SSH";
        case 80: return "HTTP";
        case 443: return "HTTPS";
        case 3306: return "MySQL";
        case 6379: return "Redis";
        case 8080: return "HTTP-Proxy";
        default: return "Unknown";
    }
}

int scan_port(const char *ip, int port, int timeout_sec) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    struct timeval tv;
    tv.tv_sec = timeout_sec;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    int ret = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    close(sock);
    return ret == 0 ? 1 : 0;
}

void scan_range(const char *ip, int start, int end) {
    printf("\n[*] Scanning %s ports %d-%d...\n", ip, start, end);
    printf("----------------------------------------\n");

    for (int port = start; port <= end; port++) {
        if (scan_port(ip, port, 1) == 1) {
            printf("[+] Port %d open\tService: %s\n", port, get_service(port));
        }
    }

    printf("----------------------------------------\n");
    printf("[*] Scan finished.\n\n");
}

int main() {
    char ip[30];
    int start, end;

    printf("==== C Network Asset Scanner ====\n");
    printf("Target IP: ");
    scanf("%s", ip);
    printf("Start port: ");
    scanf("%d", &start);
    printf("End port: ");
    scanf("%d", &end);

    scan_range(ip, start, end);
    return 0;
}
