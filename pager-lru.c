/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * This file contains the skeleton for an LRU pager
 */

#include <stdio.h> 
#include <stdlib.h>
#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proc;
    int page;
    int temp;
    int final;

    /* initialize timestamp array on first run */
    if (!initialized) {
        for (proc=0; proc < MAXPROCESSES; proc++) {
            for (page=0; page < MAXPROCPAGES; page++) {
                timestamps[proc][page] = 0; 
            }
        }
        initialized = 1;
    }
    
    /* TODO: Implement LRU Paging */
    for (proc = 0; proc < MAXPROCESSES; proc++){//loop thru processes
        if (q[proc].active){  //check proc active
            page = q[proc].pc / PAGESIZE;//get current proc page
            if(!q[proc].pages[page] && !pagein(proc,page)){ //check pagein fails go fix and pageout
                temp = tick; //set tick to temp var
                for (int i = 0; i < MAXPROCPAGES; i++){//loop thru pages
                    if (q[proc].pages[i] && timestamps[proc][i] < temp){ //if page not the oldest + swapped
                        temp = timestamps[proc][i];//set new tick to temp
                        final = i;//set to var to page out
                    }
                }
                pageout(proc,final);//page out on completion
                break;
            }
            timestamps[proc][page] = tick;//update proc+page to tick
        }
    }

    /* advance time for next pageit iteration */
    tick++;
} 
