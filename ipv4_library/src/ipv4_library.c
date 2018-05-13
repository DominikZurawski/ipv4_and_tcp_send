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

	    //Ip checksum
	    iph->check  = csum ((unsigned short *) datagram, iph->tot_len);

	return (unsigned short *) datagram;

}


