#include <dlfcn.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <net/if.h>
#include "main_program.h"
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

struct list *head = NULL;	//head of the list, początek listy wiazanej


void LadujListe ( int *count, char *dtgr ){ // ładowanie danych do listy
	for ( int i = 0; i != *count; i++ )
		InsertElement ( dtgr );
}
//rezerwacja pamieci na elementy listy
struct list *ReserveMemory ( char *datagram ){
	//create new list, węzeł
	struct list *new_node;
	static int id = 1;

	//rezerwacja pamięci na nowy "wezeł" listy
	new_node = malloc(sizeof (struct list));

	if (new_node == NULL) {
		printf("Cannot create new node");
		return NULL;
	}
	//add data to new node
	new_node->id = id;
	id++;
	new_node-> datagram = datagram;
	new_node->next = NULL;
	new_node->prev = NULL;

	//return address
	return new_node;
}

//fwlozenie nowego elemntu do listy
void InsertElement ( char *datagram ){

	struct list *temp = head;
	struct list *new_node = ReserveMemory ( datagram );


	if (head == NULL){
		head = new_node;
		return;
	}

	while (temp->next != NULL) //goto end of list
		temp = temp->next;

	//add new node to the end
	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = NULL;
}
//funkcja zwraca nagłowek naglowek listy, poczatek
struct list * ReturnHead () {
	return head;
}

//funkcja usuwa liste
void UsunListe (){

	struct list *temp = head;
	struct list *del = NULL;

	while ( temp != NULL ){
		del = temp;
		temp = temp -> next;
		free (del);
	}
	head = NULL;

}
//funkcja wysylająca pakiety z listy
int Send ( char *interface ){

	char *datagram = head -> datagram;
	struct iphdr *iph = (struct iphdr *) datagram;

	//open socket, zeby miec gdzie wysłać
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_TCP);
		if (s == -1){
			printf ("\nSocket not opened\n");
			return EXIT_FAILURE;
		}

	struct sockaddr_in sin; //dane do wysyłania
	sin.sin_family = AF_INET;
	sin.sin_port = htons (80); //htons - zamiana kolejnośći ze sposobu zapisu bajtów w procesorze na kolenosc bajtow w sieci
	sin.sin_addr.s_addr = iph->daddr;

	struct ifreq ifr;	//struct to take name of interface

	memset(&ifr, 0, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", interface); //formatuje dane do znalezienia interfejsu
	if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {		//find typed interface
			perror("ioctl() failed to find interface ");
			return (EXIT_FAILURE);
		}

	if (setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {	//bind socket to interface, łaczy socket z interfejsem
		printf ("\nNot binded\n");
		return EXIT_FAILURE;
	}


	while ( head != NULL ) {	//go to end of list

		if (sendto (s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof (sin)) < 0){	//send packet
			perror("Bład wysyłania: ");
			return EXIT_FAILURE;
		}

		else
			printf ("Wysłano pakiet o długości: %d \n" , iph->tot_len);

		head = head -> next;	//go to next node
	}
	close (s);	//close socket
	//free ( &(head -> datagram));
	UsunListe ();	//delete list

	//free (interface);
	return EXIT_SUCCESS;
}




