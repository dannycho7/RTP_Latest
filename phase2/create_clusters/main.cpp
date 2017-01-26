/** This project is used to generate clusters; fragment data and index data within each cluster.
 *  Author: Nimisha
 **/
#include <stdlib.h>
#include <cstring>
#include "XMLDataParser.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc != 3)
    {
        cout << "format: ./gen_cluster <data_file_path> <choice_of_representative>" << endl;
        exit(1);
    }

    istringstream iss( argv[2] );
    int val;
    RepresentativeChoice choice;
    if ((iss >> val) && iss.eof() && (val <= 2)) // Check eofbit
    {
        choice = (RepresentativeChoice)(val-1); //enum values start from 0
    }
    else{
        cout << "invalid <choice_of_representative>: should be between 1 and 2" << endl;
        exit(1);
    }

    //parse XML data file
    auto return_code = EXIT_SUCCESS;
    try{
        string data_file_path = string(argv[1]);
        std::ifstream is(data_file_path.c_str());
        if (!is)
          throw xmlpp::exception("Could not open file " + data_file_path);

        long chunk_size = 1024;
        char buffer[chunk_size];
        const size_t buffer_size = sizeof(buffer) / sizeof(char);

        //Parse the file in chunks of "chunk_size" characters:
        XMLDataParser parser;
        parser.set_substitute_entities(true);
        parser.setRepresentativeChoice(choice);
        do
        {
          std::memset(buffer, 0, buffer_size);
          is.read(buffer, buffer_size-1);
          if(is.gcount())
          {
            // We use Glib::ustring::ustring(InputIterator begin, InputIterator end)
            // instead of Glib::ustring::ustring( const char*, size_type ) because it
            // expects the length of the string in characters, not in bytes.
            Glib::ustring input(buffer, buffer+is.gcount());
            parser.parse_chunk(input);
          }
        }
        while(is);
        parser.finish_chunk_parsing();
    }
    catch(const xmlpp::exception& ex){
        std::cerr << "Incremental parsing, libxml++ exception: " << ex.what() << std::endl;
        return_code = EXIT_FAILURE;
    }
    return return_code;
}


