/*
 ============================================================================
 Name        : tpc_library.c
 Author      : Dominik Żurawski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<netinet/ip.h>
#include "tpc_library.h"

void tcp_rfc(unsigned char *datagram){//unsigned short iph,char size_ipv4, funkcja) {

	struct pseudo_header *psh = malloc ( sizeof (struct pseudo_header)); //RFC 793
	char *pseudogram;

	struct nagl_tcp *tcph = (struct nagl_tcp *) (datagram + sizeof(struct iphdr));
	struct iphdr *iph = (struct iphdr *) datagram;

	char *data = datagram + sizeof(struct iphdr) + sizeof(struct nagl_tcp);

	iph->protocol = IPPROTO_TCP;

	memset (tcph, 0 ,iph->tot_len); //Wypełnia kolejne bajty w pamięci ustaloną wartością.

	strcpy (data, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	iph->tot_len = sizeof(struct iphdr) + sizeof (struct nagl_tcp) + strlen(data);
	puts("ok");
	//TCP Header
	   tcph->Source_port = htons (1234);
	    tcph->Destination_port = htons (7889);
	    tcph->Sequence_number = 0;
	    tcph->Acknowledgment_number = 0;
	    tcph->Data_offset = 5;  //tcp header size, 5 is minimum, 15 is maximum
	    tcph->Reserved=0;
	    tcph->FIN=0;
	    tcph->SYN=1;
	    tcph->RST=0;
	    tcph->PSH=0;
	    tcph->ACK=0;
	    tcph->URG=0;
	    tcph->Window_Size= htons (5840); /* maximum allowed window size */
	    tcph->Checksum = 0; //leave checksum 0 now, filled later by pseudo header
	    tcph->Urgent_pointer = 0;	//only search if URG is set, tell about value a packet

	        psh->source_address = iph->saddr;//source; //od nagłowka ipv4
	        psh->dest_address = iph->daddr;//sin.sin_addr.s_addr;//destination;		//od nagłowka ipv4
	        psh->zero = 0;
	        psh->PTCL = IPPROTO_TCP;
	        psh->tcp_length = htons (sizeof(struct nagl_tcp) + strlen(data));	//dl_data(size_ipv4));//strlen(data) ); //data od nagłowka ipv4 lub w głownym programie

	        int psize = sizeof(struct pseudo_header) + sizeof(struct nagl_tcp) + strlen(data);//dl_data(size_ipv4);//strlen(data);
	        pseudogram = malloc(psize);

	        memcpy(pseudogram , (char*) psh , sizeof (struct pseudo_header));
	        memcpy(pseudogram + sizeof(struct pseudo_header) , tcph , sizeof(struct nagl_tcp) + strlen(data));//dl_data(size_ipv4));//strlen(data));

	        tcph->Checksum = csum( (unsigned short*) pseudogram , psize);

}
