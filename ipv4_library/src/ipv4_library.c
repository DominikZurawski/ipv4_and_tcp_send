/*
 ============================================================================
 Name        : ipv4_library.c
 Author      : Dominik Żurawski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memset
#include <arpa/inet.h>
//#include <sys/socket.h>
#include "ipv4_library.h"

unsigned short ipv4_rfc(){ //char size_tcp,unsigned short dl_data ){
	char *data;//*datagram , source_ip[32] , destination_ip[32], *data ;

	char *datagram = malloc ( 4096 );
	memset (datagram, 0, 4096); //clear memory

	struct iphdr *iph = (struct iphdr *) datagram;


	data = (char *)datagram + sizeof(struct iphdr); //  + size_tcp; //sizeof(struct tcphdr);
	strcpy(data , "ABCDEFGHIJ");

	//Fill in the IP Header
	    iph->ihl = 5;	//5 is minimum
	    iph->version = 4;
	    iph->tos =0;
	    iph->tot_len = sizeof (struct iphdr) + strlen(data);
	    iph->id= htonl (54321); //Id of this packet
	    iph->frag_off = 0;
	    iph->ttl = 64;
	    iph->protocol = IPPROTO_TCP;	// 6 =IPPROTO_TCP; /* Transmission Control Protocol.  */
	    iph->check = 0;      //Set to 0 before calculating checksum
	    iph->saddr = inet_addr ( "192.168.1.1" );
	    iph->daddr = inet_addr ("1.2.3.4");

	    char input [32];
	    int odpowiedz;
	   	   printf ("Czy chcesz zmienić wartości domyslne protokolu IPv4,0-nie/1-tak?\n");
	   	   fgets (input, 32, stdin);
	   	   if(atoi(input) == 1){

	   	    	printf ("Fragmentation offset (0): ");
	   	    	fgets (input, 32, stdin);
	   	    	        if (atoi(input)== 0)
	   	    	                printf(" ");
	   	    	        else
	   	    	                iph->id = htons (atoi(input));

	   	    	        printf ("Fragmentation offset (0): ");
	   	    	        fgets (input, 32, stdin);
	   	    	        if (atoi(input)== 0)
	   	    	        	printf(" ");
	   	    	        else
	   	    	                iph->frag_off = atoi (input);

	   	    	        printf ("Time to live (64): ");
	   	    	        //fgets (input, 32, stdin);
	   	    	        if (atoi(input)== 0)
	   	    	        	printf(" ");
	   	    	        else{
	   	    	               iph->ttl = atoi (input);

	   	    	        }
					 printf ("Source address (192.168.1.1): ");
							fgets (input, 32, stdin);
							if (atoi(input)== 0)
								printf(" ");
							else
									iph->saddr = inet_addr(input);

							printf ("Destination address (8.8.8.8): ");
							fgets (input, 32, stdin);
							if (atoi(input)== 0)
								printf(" ");
							else
									iph->daddr = inet_addr(input);
	   	    }

	    //Ip checksum
	    iph->check  = csum ((unsigned short *) datagram, iph->tot_len);

	return (unsigned short *) datagram;

}


