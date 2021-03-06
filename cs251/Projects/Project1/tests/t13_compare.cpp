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

  START("List::compare_with test Suite (15 pts)"); 
  {
    PtsPer = 1.875;

    lsts[0] = new List<int>();
    lsts[1] = one_to_n_lst(1);
    lsts[2] = one_to_n_lst(1);
    lsts[3] = new List<int>();

    TEST_RET(lsts[0]->compare_with(*lsts[3]), 
        "empty lst vs empty list!",
        0,  PtsPer);

    TEST_RET(lsts[1]->compare_with(*lsts[2]), 
        "identical singletons",
        0,  PtsPer);

    TEST_RET(lsts[0]->compare_with(*lsts[1]), 
        "empty-list first!",
        -1,  PtsPer);

    TEST_RET(lsts[1]->compare_with(*lsts[0]), 
        "empty-list first! (args flipped)",
        1,  PtsPer);

    cleanup();

    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3, 4};

    lsts[0] = arr2list(a, 3);
    lsts[1] = arr2list(b, 4);

    TEST_RET(lsts[0]->compare_with(*lsts[1]), 
        "1st list prefix of second",
        -1,  PtsPer);

    TEST_RET(lsts[1]->compare_with(*lsts[0]), 
        "2nd list is prefix of first",
        1,  PtsPer);

    cleanup();

    int aa[] = {1, 2, 3};
    int bb[] = {1, 2, 4};

    lsts[0] = arr2list(aa, 3);
    lsts[1] = arr2list(bb, 3);
    TEST_RET(lsts[0]->compare_with(*lsts[1]), 
        "differ at last position",
        -1,  PtsPer);

    cleanup();

    int c[] = {3, 3, 1, 3, 8, 12};
    int d[] = {3, 4, 99};

    lsts[0] = arr2list(c, 6);
    lsts[1] = arr2list(d, 3);
    TEST_RET(lsts[0]->compare_with(*lsts[1]), 
        "longer list comes first",
        -1,  PtsPer);

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
