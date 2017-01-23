all:
	g++ -o binary_index_gen binary_index_gen.cc serializer.cc LineScanner.cc stemmer.cc coding.cc -lssl -lcrypto
	g++ -o index_search index_search.cc index_searcher.cc serializer.cc stemmer.cc -lssl -lcrypto
