/*
 * tpc_library.h
 *
 *  Created on: 30 kwi 2018
 *      Author: root
 */

#ifndef TPC_LIBRARY_H_
#define TPC_LIBRARY_H_

unsigned short csum(unsigned short *ptr,int nbytes);
//char size_tcp(void);
void tcp_rfc(unsigned char * datagram);//unsigned short iph,char size_ipv4);
//unsigned short dl_data(char size_ipv4);
//char *pseudogram, datagram[4096],source_ip[32];



struct nagl_tcp {
	unsigned short Source_port;
	unsigned short Destination_port;
	unsigned int Sequence_number;
	unsigned int Acknowledgment_number;
	unsigned char Data_offset:4;
	unsigned char Reserved:3;
	unsigned char NS,
				CWR,
				ECE,
				URG,
				ACK,
				PSH,
				RST,
				SYN,
				FIN;
	unsigned short Window_Size;
	unsigned short Checksum;
	unsigned short Urgent_pointer;
	unsigned int Options;
};
/*struct nagl_eth {
		unsigned char	destination_mac[6];
		unsigned char	source_mac[6];
		unsigned short	ether_type;
	};*/

struct pseudo_header
{
	unsigned long source_address;
    unsigned long dest_address;
    unsigned char zero;
    unsigned char PTCL;
    unsigned int tcp_length;
};

unsigned short csum(unsigned short *ptr,int nbytes)
{
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }
    if(nbytes==1) {
        oddbyte=0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }

    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;

    return(answer);
}



#endif /* TPC_LIBRARY_H_ */
