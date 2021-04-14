#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

int arrs[][5] = {
		{ 1, 2, 3, 4, 5} ,
		{ 5, 4, 3, 2, 1},
		{ 0, 2, 3, 4, 5} ,
		{ 1, 2, 3, 4, 0} ,
		{ 0, 0, 0, 0, 0} ,   //IDX-4
		{ 1, 0, 0, 0, 0} ,   //IDX-5
		{ 0, 0, 0, 0, 1},    //IDX-6
		{ 0, 1, 0, 1, 0}     //IDX-7
	     };

using namespace std;

int testB(int n) {
  List<int> *lst;
  int ndel;

	 lst = rem_all_hard_caseB(n);

   ndel = lst->fast_remove_all(0);

   delete lst;

   return ndel == n;
}

int testA(int n) {
  List<int> *lst;
  int ndel;

	 lst = rem_all_hard_caseA(n);

   ndel = lst->fast_remove_all(0);

   delete lst;

   return ndel == n;
}

int main(int argc, char *argv[]){
  int n = __N;
  int ntrials = __NTRIALS;
  int i, dummy;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);

  printf("STARTING AUTO-TEST WITH: \n");
  printf("    N (Big Problem Size) = %i\n", n);
  printf("    NUM_TRIALS       = %i\n", ntrials);
  printf("USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");
  printf("    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  printf("EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  printf("    %s 9999 100000\n\n", argv[0]);

  printf("here we go...\n\n");

  START("List::fast_remove_all test Suite (20 pts)"); 
  {
    int i;


    PtsPer = 2.5;


    lsts[0] = rem_all_hard_caseA(10);
    TEST_RET(lsts[0]->fast_remove_all( 0), 
        "Ten 1's followed by 10 0's (return val test)",
        10, 2.5);

    TEST_RET(n_ones(lsts[0], 10), 
        "after deleting 0's, list should be exactly 10 1's",
        1, PtsPer);

    cleanup();
    lsts[0] = rem_all_hard_caseB(10);
    TEST_RET(lsts[0]->fast_remove_all( 0), 
        "(5 1's) (5 0's) (5 1's) (5 0's) test (return val test)",
        10, PtsPer);

    TEST_RET(n_ones(lsts[0], 10), 
        "after deleting 0's, list should be exactly 10 1's",
        1, PtsPer);


    cleanup();

    PtsPer = 5.0;

    TIME_RATIO2(testA(n), testA(2*n),
        "runtime test n 1's followed by n 0's",
        1, 1, 2.1, PtsPer);

    cleanup();

    TIME_RATIO2(testB(n), testB(2*n), 
        "runtime test n 1's followed by n 0's",
        1, 1, 2.1, PtsPer);


    cleanup();

  }
  END

  printf("\n\nPOST-MORTEM...\n");
  printf("YOU JUST RAN THIS AUTO-TEST WITH: \n");
  printf("    N (Big Problem Size) = %i\n", n);
  printf("    NUM_TRIALS       = %i\n\n", ntrials);
  printf("IF YOU RECEIVED A ");
  _red_txt();
  printf("WARNING ");
  _normal_txt();
  printf(" ABOUT UNRELIABLE RUNTIME MEASUREMENTS\n");
  printf("AND INCREASING NUMBER OF TRIALS / PROBLEM SIZE\n");
  printf("HERE IS HOW YOU DO IT:\n\n");
  printf("  USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");


  _cyan_txt();
  printf("    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  _normal_txt();
  printf("  EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  _cyan_txt();
  printf("    %s 9999 100000\n\n", argv[0]);
  _normal_txt();

  cleanup();

  return 0;
}
