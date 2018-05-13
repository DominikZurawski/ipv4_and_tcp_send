/*
 * ipv4_library.h
 *
 *  Created on: 28 kwi 2018
 *      Author: root
 */

#ifndef IPV4_LIBRARY_H_
#define IPV4_LIBRARY_H_

#include <netinet/ip.h>
//char size_ipv4(void);
//unsigned short total_length(void);
unsigned short ipv4_rfc();//char size_tcp,unsigned short dl_data);
unsigned short csum(unsigned short *ptr,int nbytes);

/*
struct nagl_ipv4 {
		unsigned char	ihl:4,		//inna kolejnosc
						version:4;//
		unsigned char	ecn:2,			//kolejnosc
						dscp:6;//
		unsigned short	total_length;//
		unsigned short	identification;//
		unsigned short	fragment_offset:13,//	//odwrotnie wpisana kolejnosc
						flags:3;//
		unsigned char	time_to_live;//
		unsigned char	protocol;  				//mozna sprawdzic rodzaj protokolu
		unsigned short	header_checksum;//
		unsigned int	source_ip_adress;//
		unsigned int	destination_ip_adress;//
	};*/

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

#endif /* IPV4_LIBRARY_H_ */
