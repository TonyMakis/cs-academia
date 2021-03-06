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


int test(int n) {
  List<int> *lst;
  List<int> *m;
  int success = 1;
  int i, x;

  lst = new List<int>();

  for(i=0; i<n; i++) {
    x = i % (n/4);
    lst->push_front(x);
  }
  m = lst->suffix_maxes();

  // minimal correctness check:
  //
  m->pop_front(x);
  if(x != (n/4)-1)
    success = 0;

  delete m;
  delete lst;
  return success;
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

  START("List::suffix_maxes test Suite (15 pts)"); 
  {
    PtsPer = 1.5;

    lsts[0] = one_to_n_lst(1);
    lsts[1] = lsts[0]->suffix_maxes();

    TEST_RET(lsts_equal_destructive(lsts[0], lsts[1]), 
        "suff-max of singleton is the singleton!",
        1,  PtsPer);

    cleanup();

    int a[] = {4, 3, 2, 1};
    lsts[0] = arr2list(a, 4);
    lsts[1] = lsts[0]->suffix_maxes();

    TEST_RET( lsts_equal_destructive(lsts[0], lsts[1]), 
        "suff-max of descending seq is seq itself!",
        1,  PtsPer);

    cleanup();

    int b[] = {0, 0, 100, 1, 1, 10};
    int c[] = {100, 100, 100, 10, 10, 10};

    lsts[0] = arr2list(b, 6);
    lsts[1] = lsts[0]->suffix_maxes();
    lsts[2] = arr2list(c, 6);

    TEST_RET( lsts_equal_destructive(lsts[1], lsts[2]), 
        "testing {0,0,100,1,1,10}",
        1,  PtsPer);
    TEST_RET( eq2array(lsts[0], b, 6),
        "making sure original list unchanged",
        1,  PtsPer);

    cleanup();
    int bb[] = {4, 7, 3, 5, 1};
    int cc[] = {7, 7, 5, 5, 1};

    lsts[0] = arr2list(bb, 5);
    lsts[1] = lsts[0]->suffix_maxes();
    lsts[2] = arr2list(cc, 5);

    lsts[1]->print();

    TEST_RET( lsts_equal_destructive(lsts[1], lsts[2]), 
        "testing {4,7,3,5,1}",
        1,  PtsPer);
    TEST_RET( eq2array(lsts[0], bb, 5),
        "making sure original list unchanged",
        1,  PtsPer);


    cleanup();




    TIME_RATIO2(test(n), test(2*n), 
        "runtime test (with minimal correctness test)",
        1, 1, 2.2, 6.0);


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
