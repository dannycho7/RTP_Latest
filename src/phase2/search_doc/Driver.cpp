#include <iostream>
#include "Phase2_Searcher.h"


int main(int argc, char** argv)
{
    if (argc !=2)
    {
        cout << "need one parameter for query_len" << endl;
        exit(1);
    }
    Phase2_Searcher* searcher =  new Phase2_Searcher();
    searcher->query_len=atoi(argv[1]);
    searcher->init();
    searcher->read_index();
    searcher->read_search_frag();
    searcher->intersection();
    //intersection1();
    //print_vid();
    searcher->scoring();
    return 0;
}
