/*
 * File: pager-predict.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknowns
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a predictive pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) 
{ 
    /* Static vars */
    static int tick = 1; // artificial time
    static int process = 0; //which process to run first 

    /* Local vars */
    int proctmp;
    int pagetmp;
    int pc;
    int page;

    for(proctmp = process; proctmp<MAXPROCESSES; proctmp++) //alternate through processes for fairness
    { 
    /* Is process active? */
        if(process == MAXPROCESSES-1) // move among processes in circular queue
        {
            process = 0;
        }
        else
        {
            process++;
        }
        if(q[proctmp].active)  // check if process is active
        {
            pc = q[proctmp].pc;                // program counter for process
            page = pc/PAGESIZE;         // page the program counter needs
          /* Is page swaped-out? */
            if(!q[proctmp].pages[page]){
            /* Try to swap in */
                pagein(proctmp,page);
            }
            if(page == 0) // pages in and out based on the current spot in the program and the overlap between all the programs for what they need paged in 
            {
                if(!q[proctmp].pages[1])
                {
                    pagein(proctmp,1);
                }


                for(int i = 2; i <15;i++) // correct for incorrect loading
                {
                    pageout(proctmp, i); // never swap , only pageout when pages are no longer needed
                }
            }
            if(page == 1)
            {
                if(!q[proctmp].pages[2])
                {
                    pagein(proctmp,2);
                }
                //never pageout page 0 for any process, since it is the most commonly used page
            }
            if(page == 2) // example of the general case where the last page should be pageod out and the next page should be paged in
            {
                if(!q[proctmp].pages[3])
                {
                    pagein(proctmp,3);
                }


                pageout(proctmp, 1);
            }
            if(page == 3)
            {
                if(!q[proctmp].pages[0]) // needed for program 5
                {
                    pagein(proctmp,0);
                }
                if(!q[proctmp].pages[4]) // general case, needed for every process
                {
                    pagein(proctmp,4);
                }
                if(!q[proctmp].pages[10]) // needed for program 1
                {
                    pagein(proctmp,10);
                }
                if(!q[proctmp].pages[11]) // needed for program 1, since jump to page 10 only has a few instructions left before 11 will be needed
                {
                    pagein(proctmp,11);
                }


                pageout(proctmp, 2);
            }
            if(page == 4)
            {
                if(!q[proctmp].pages[5])
                {
                    pagein(proctmp,5); 
                }


                pageout(proctmp, 3); // correct for incorrect loading
                pageout(proctmp, 10); // "
                pageout(proctmp, 11); // "

            }
            if(page == 5)
            {
                if(!q[proctmp].pages[6])
                {
                    pagein(proctmp,6);
                }


                pageout(proctmp, 4);
            }
            if(page == 6)
            {
                if(!q[proctmp].pages[7])
                {
                    pagein(proctmp,7);
                }


                pageout(proctmp, 5);
            }
            if(page == 7)
            {
                if(!q[proctmp].pages[8])
                {
                    pagein(proctmp,8);
                }


                pageout(proctmp, 6);
            }
            if(page == 8)
            {
                if(!q[proctmp].pages[9])
                {
                    pagein(proctmp,9);
                }
                if(!q[proctmp].pages[0]) // needed for program 2
                {
                    pagein(proctmp,0);
                }


                pageout(proctmp, 7);
            }
            if(page == 9)
            {
                if(!q[proctmp].pages[10])
                {
                    pagein(proctmp,10);
                }


                pageout(proctmp, 8);
                pageout(proctmp, 13); // correct for incorrect loading
                pageout(proctmp, 14); // "
            }
            if(page == 10)
            {
                if(!q[proctmp].pages[11])
                {
                    pagein(proctmp,11);
                }


                pageout(proctmp, 9);
                pageout(proctmp, 3);// correct for incorrect loading
                pageout(proctmp, 4); // "
            }
            if(page == 11)
            {
                if(!q[proctmp].pages[0]) // needed for program 1
                {
                    pagein(proctmp, 0);
                }
                if(!q[proctmp].pages[12])
                {
                    pagein(proctmp, 12);
                }


                pageout(proctmp, 10);
            }
            if(page == 12)
            {
                if(!q[proctmp].pages[13])
                {
                    pagein(proctmp,13);
                }
                if(!q[proctmp].pages[9]) // preloading for program 3, improves performance
                {
                    pagein(proctmp,9);
                }
                if(!q[proctmp].pages[0]) // "
                {
                    pagein(proctmp, 0);
                }


                pageout(proctmp,11);
            }
            if(page == 13)
            {
                if(!q[proctmp].pages[9]) // needed for program 3
                {
                    pagein(proctmp,9);
                }
                if(!q[proctmp].pages[14])
                {
                    pagein(proctmp, 14);
                }
                if(!q[proctmp].pages[0]) // needed for program  3
                {
                    pagein(proctmp,0);
                }


                pageout(proctmp, 12);
            }
            if(page == 14)
            {
                pageout(proctmp, 9); // correct for incorrect loading
            }
            
        }
        else // if process is in active, deallocated all the pages it has in memory
        {
            for(pagetmp = 0; pagetmp < q[proctmp].npages; pagetmp++)
            {
                if(q[proctmp].pages[pagetmp] == 1)
                {
                    pageout(proctmp, pagetmp);
                }
            }
        }
    }
    tick++;
} 
