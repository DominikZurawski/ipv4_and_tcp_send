/*
 ============================================================================
 Name        : main_program.c
 Author      : Dominik Żurawski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_program.h"
#include <dlfcn.h>
#include <netinet/in.h>
#include <error.h>

int main (int argc, char** argv) {

		if(argc != 3) {
			puts("Nieprawidłowa liczba argumentow:");
			puts("sudo ./main_program [count packet] [count protocol: 0 ipv4 or 1 tcp]");
			exit(1);
		}
	system("clear");

	char cmd [30],input [32];
	int *count, result;
	char *interface ;

	void * Biblioteka_ipv4 = malloc(sizeof (void));
	void * Biblioteka_tcp = malloc(sizeof (void));

	unsigned short *datagram;
	unsigned short * (*ipv4_rfc) () = malloc (sizeof (unsigned short *));
	void (*tcp_rfc) (unsigned char *) = malloc (sizeof(void));

	datagram = malloc (sizeof (4096));
	count = malloc (sizeof (int));
	interface = malloc (sizeof (char)*32);

	*count=atoi(argv[1]);

		printf ("Wybierz interfejs.\n");
				//usu sys command
				sprintf(cmd, "/bin/ip link");
				system(cmd);

				printf ("Name:");
				fgets ( input, 32, stdin );	//get name of interface
				memcpy ( interface, input, strlen (input)-1 ); //Usuwa znak końca linii, żeby można było znaleźć interfejs


	result =atoi(argv[2]);

	Biblioteka_ipv4 = dlopen("/home/domino/eclipse-workspace/ipv4_library/src/ipv4_library.so", RTLD_LAZY); //lub RTLD_NOW// otwarcie biblioteki RTLD_LAZY -
																//wskazniki na funkcie wewnetrzne sa budowane dopiero w trakcie wywolania dlsym

	ipv4_rfc = dlsym(Biblioteka_ipv4, "ipv4_rfc"); // pobranie wskznika na odpowiednia funckje podana za pomoca nazwy
	datagram = (*ipv4_rfc)();


	if (result == 1){ // warunek przekazywanay z maina

		Biblioteka_tcp = dlopen("/home/domino/eclipse-workspace/tpc_library/src/tpc_library.so", RTLD_LAZY);

		tcp_rfc= dlsym(Biblioteka_tcp, "tcp_rfc");
		(*tcp_rfc) ((unsigned char *) datagram);

	}


	LadujListe( count, (char*) datagram );
	Send( interface );
	EXIT_SUCCESS;
}
