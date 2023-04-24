#include <stdio.h> 
#include <stdlib.h>
#include "simulator.h"
void pageit(Pentry q[MAXPROCESSES])
{ 
    int page;
    int proc;
    for(proc = 0; proc < MAXPROCESSES; proc++){
        if (q[proc].active){//check proc active
            int predArr[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//prediction array intitialization
            page = q[proc].pc/PAGESIZE;//get current proc page
            predArr[page] = 1;//set current proc page to 1 in prediction array
            switch(page){
                case 2:
                    predArr[0] = 1;
                    predArr[3] = 1;
                    predArr[4] = 1;
                case 3:
                    predArr[0] = 1;
                    predArr[4] = 1;
                    predArr[10] = 1;
                case 7:
                    predArr[0] = 1;
                    predArr[8] = 1;
                    predArr[9] = 1;
                case 8:
                    predArr[0] = 1;
                    predArr[9] = 1;
                    predArr[10] = 1;
                case 10:
                    predArr[0] = 1;
                    predArr[11] = 1;
                    predArr[12] = 1;
                case 11:
                    predArr[0] = 1;
                    predArr[1] = 1;
                    predArr[12] = 1;
                case 12:
                    predArr[0] = 1;
                    predArr[9] = 1;
                    predArr[13] = 1;
                case 13:
                    predArr[0] = 1;
                    predArr[14] = 1;
                    predArr[9] = 1;
                    predArr[10] = 1;
                case 14:
                    predArr[0] = 1;
                    predArr[2] = 1;
                default:
                //default is first page then next two as the predictor (testing with this and edge case first)
                    predArr[0] = 1;
                    predArr[page + 1] = 1;
                    predArr[page + 2] = 1;
        }
            for(int i = 0; i < 15; i++){//iterate through predArr and pageout and pagein based on bit(1/0) of page
                if (predArr[i] == 0){
                    pageout(proc,i);//evict
                }else{
                    pagein(proc,i);//success
                }
            }

        }
    }
}