/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES])
{ 
    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];
    static int process = 0; // first process to check if active

    /* Local vars */
    int proctmp;
    int pageswap;
    int pagetmp;
    int pc;
    int page;

    /* initialize static vars on first run */
    if(!initialized){
	for(proctmp=0; proctmp < MAXPROCESSES; proctmp++){
	    for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++){
		timestamps[proctmp][pagetmp] = 0;
	    }
	}
	initialized = 1;
    }

    for(proctmp = process; proctmp<MAXPROCESSES; proctmp++)  // rotate through running processes for fairness 
    { 
    /* Is process active? */
        if(process == MAXPROCESSES-1) // update processes to run in circular queue
        {
            process = 0;
        }
        else
        {
            process++;
        }
        if(q[proctmp].active) // check if process is active and needs pages
        {
            pc = q[proctmp].pc;                // program counter for process
            page = pc/PAGESIZE;         // page the program counter needs
            int success = 0;
          /* Is page swaped-out? */
            if(!q[proctmp].pages[page])
            {
            /* Try to swap in */
                success = pagein(proctmp,page);
                if(!success) // if page cannot be paged in, memory is full and something needs to be swapped out
                {
                    int min = tick;
                    for(pagetmp=0; pagetmp < q[proctmp].npages; pagetmp++) // find local LRU
                    {
                        if(q[proctmp].pages[pagetmp] == 1)
                        {
                                min = timestamps[proctmp][pagetmp]; // keep updating min until process with lowest timestamp is found
                                pageswap = pagetmp;
                        }  
                    }
                    if(min != tick) // if a min value was found
                    {
                        if(!pageout(proctmp, pageswap))
                        {
                            printf("pageout failed\n");
                        }  
                        
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    timestamps[proctmp][page] = tick; // when page is paged in, update timestamp to be current time
                }
            }
            else
            {
                timestamps[proctmp][page] = tick; // when page is accessed, update timestamp to be current time
            }
        }
    }
    /* advance time for next pageit iteration */
    tick++;
} 
