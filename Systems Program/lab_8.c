#include<stdio.h> 
#include<stdlib.h> 
#include<ifaddrs.h> 
#include<sys/socket.h> 
#include<netdb.h> 
 
int main() 
{ 
    struct ifaddrs *addresses; 
    if (getifaddrs(&addresses) == -1) 
    { 
        printf("Error getting network info\n"); 
    } 
    struct ifaddrs *address = addresses; 
    while (address){ 
        int family = address->ifa_addr->sa_family; 
        if (family == AF_INET){
            char name[100];
            int size = sizeof(struct sockaddr_in);
            getnameinfo(address->ifa_addr, size, name, sizeof(name), 0, 0, 0);
            printf("Interface Name for IPv4: %s\n", name); 
        }
        if (family == AF_INET6){ 
            char name[100];
            int size = sizeof(struct sockaddr_in);
            getnameinfo(address->ifa_addr, size, name, sizeof(name), 0, 0, 0);
            printf("Interface Name for IPv6: %s\n", name); 
        }
        address = address->ifa_next;

    }
 
    return 0; 
} 