/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:38:21 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 14:00:52 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

tas heap partage genre tous les threads dans le stacks sont dedans 


#include <pthread.h>

pour compiler on utilise -lpthread (-l pour lier avec la biblotheque pthread, comme le -I . qui indique le chemin ou se situe le .h)

on utilise un thread pour lui assigner une tache specifique pendant qu''on fait autre chose

on utilise toujours *void car la bibliotheque pthread est generique  


fonction de base :
void faireqqlchose() {
}

variante :
void *faireqqlchosepourthread() {
    faireqqlchose();
    return NULL;
}

pthread_t thread_perso;
int ok = pthread_create/*existe deja*/(&thread_perso, NULL, faireqqlchosepourthread, NULL);

pthread_create place l'id du thread q'on a cree dans notre thread_perso
ensuite mtn que la variante fait son taff le thread principal peut faire autre chose

pour faire attendre le thread :
int ok = pthread_join(%thread_perso, NULL);
si tout est bon renvoie ok sinon si par ex y'a pas le bon nom de thread ou qu'il
a deja attendu on renvoie autre chose

thread avec parametre :
void MangeCrepes(int nbCrepes) {
    /*MangeCrepes(10);*/
}

void *MangeCrepesPourThread(void *p) {
    MangeCrepes(*(int *) p); /*on caste pour que p devienne un entier valide vu qu'il etait en void, la premiere * permet d'acceder au nouvel entier*/
    return NULL;
}

pthread_t thread_perso;
int *p = malloc(sizeof(int));
if (p == NULL) exit(EXIT_FAILURE);
*p = 10;
int ok = pthread_create(&thread_perso, NULL, (void*) MangeCrepes, p);


si on veut rajouter un parametre supplementaire :
void mangecrepes(int nbCrepes, bool isRhum) {
    /*mangecrepes(10, true);*/
}

Vu qu''on a bcp de parametres on utilise des struct :
struct thread_perso_args
{
    int nbCrepes;
    bool isRhum;
};

void *mangecrepespourthread(void *ptr_args)
{
    struct thread_perso_args *ptr = ptr_args;
    mangecrepes(ptr->nbCrepes, ptr->isRhum);
}

pthread_t thread_perso;
struct thread_perso_args *ptr = malloc(sizeof(*ptr));
if (ptr == NULL)
    exit(EXIT_FAILURE);
ptr->nbCrepes = 12230;
ptr->isRhum = true;
pthread_create(&thread_perso,  NULL, mangecrepespourthread, ptr);

c''est quoi un fork ? 
c''est creer le processus fils a partir du processus parent 

pthread_exit(EXIT_SUCCESS); /*pour sortir du thread*/