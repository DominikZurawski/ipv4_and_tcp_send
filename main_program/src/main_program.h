/*
 * main_program.h
 *
 *  Created on: 11 maj 2018
 *      Author: root
 */

#ifndef MAIN_PROGRAM_H_
#define MAIN_PROGRAM_H_

//lista
struct list {
	int id; // wypełnia się samo
	char *datagram; //wskaznik do pakietu ktory mam wyslac
	struct list *next; //wskaznik na nastepny element
	struct list *prev;
};


int Send ( char *interface );
void LadujListe ( int *count, char *dtgr );

struct list *ReserveMemory ( char *datagram );	//function to reserve memory for new list element
void InsertElement ( char *datagram );	//function to put new element at the end of the list

void UsunListe ();	//function to delete linked list
struct list * ReturnHead (); //function to return head of the list

#endif /* MAIN_PROGRAM_H_ */
