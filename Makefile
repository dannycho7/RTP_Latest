TARGET = ./target
SOURCE = ./src
CC = g++
CFLAGS = -std=c++0x
LFLAGS = -Wall $(DEBUG)
DEBUG = -g
PARSER_FLAG = -Wno-inconsistent-missing-override -Wno-deprecated -Wno-format -Wno-write-strings `pkg-config --cflags --libs libxml++-2.6 glibmm-2.4`
OPENSSL_FLAGS=-lssl -lcrypto

#flag for my local use only!!! Delete while checking in!
OPENSSL_FLAGS_MAC_ONLY=-I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib
PARSER_FLAG_MAC_ONLY = -Wno-inconsistent-missing-override -Wno-deprecated -Wno-format -Wno-writable-strings `pkg-config --cflags --libs libxml++-2.6 glibmm-2.4`

all: pre_process_data pre_process_query phase1_search_doc phase2_binary_index phase2_index_search gen_cluster convert gen_title_len phase2_search_doc

pre_process_data: 
	$(CC) $(CFLAGS) $(addprefix $(SOURCE)/pre_process_data/, Page.cpp XMLDataParser.cpp PreProcessor.cpp) -o $(TARGET)/pre_processor_data $(PARSER_FLAG)

pre_process_query:
	gcc $(addprefix $(SOURCE)/pre_process_query/, stem.c) -o $(TARGET)/pre_processor_query 

phase1_search_doc:
	$(CC) $(addprefix $(SOURCE)/data_structures/, ScoreResult.cpp) $(addprefix $(SOURCE)/phase1/search_doc/, Phase1_Searcher.cpp Driver.cpp) $(CFLAGS) -o $(TARGET)/phase1_search_doc

phase2_binary_index:
	$(CC) $(OPENSSL_FLAGS_MAC_ONLY) -o $(TARGET)/phase2_binary_index $(addprefix $(SOURCE)/phase2/index_doc/, binary_index_gen.cc serializer.cc LineScanner.cc stemmer.cc coding.cc) $(OPENSSL_FLAGS)

phase2_index_search:
	$(CC) $(OPENSSL_FLAGS_MAC_ONLY) -o $(TARGET)/phase2_index_search $(addprefix $(SOURCE)/phase2/index_doc/, index_search.cc index_searcher.cc serializer.cc stemmer.cc) $(OPENSSL_FLAGS)

gen_cluster:
	$(CC) $(CFLAGS) $(addprefix $(SOURCE)/phase2/create_clusters/, NeverLostUtil.cpp  rabin_asm.S rabin.cpp CreateCluster.cpp  Driver.cpp) -o $(addprefix $(TARGET)/, gen_cluster)

convert:	
	$(CC) $(CFLAGS) $(addprefix $(SOURCE)/phase2/create_clusters/, Convert.cpp ConvertDriver.cpp) -o $(addprefix $(TARGET)/, convert)

gen_title_len:
	$(CC) $(CFLAGS) $(addprefix $(SOURCE)/phase1/index_doc/, GenTitleLength.cpp) -o $(addprefix $(TARGET)/, gen_title_len)

phase2_search_doc:
	$(CC) $(addprefix $(SOURCE)/data_structures/, V_Occurence.cpp ScoreResult.cpp) $(addprefix $(SOURCE)/phase2/search_doc/, Phase2_Searcher.cpp Driver.cpp) $(CFLAGS) -o $(TARGET)/phase2_search_doc

clean:
	rm -rf $(TARGET)/*
	rm -f ./src/phase1/search_doc/search_frag.txt
