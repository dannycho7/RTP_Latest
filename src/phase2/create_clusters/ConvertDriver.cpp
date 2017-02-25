#include <iostream>

#include "Convert.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "need one argument" << endl;
        return 1;
    }
    Convert * convertObj = new Convert();
    convertObj->did = argv[1];
    convertObj->init();
    convertObj->read();
    convertObj->output_forward_table();
    return 0;
}