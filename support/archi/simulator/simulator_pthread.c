/**
 * @file simulator_pthread.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 12, 2016, 22:11 PM
 *
 * @brief PThread support for testing purpose (windows and linux cross-platforms)
 */

#include "simulator_pthread.h"

#include <stdio.h>

pthread_t thread_store;

static void * fn_store (void * p_data)
{
   while (1)
   {
      psleep(100);
      printf ("Remplissage du stock de articles !\n");
   }
   return NULL;
}

void simulator_pthread_init()
{
    pthread_create (&thread_store, NULL, fn_store, NULL );
    //pthread_join (thread_store, NULL);
}

