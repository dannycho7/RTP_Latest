CC = g++
CFLAGS = -std=c++0x
LFLAGS = -Wall $(DEBUG)
DEBUG = -g
PARSER_FLAG = -Wno-inconsistent-missing-override -Wno-deprecated -Wno-format `pkg-config --cflags --libs libxml++-2.6 glibmm-2.4`

all:
	$(CC) $(CFLAGS) neverlost_util.cpp  rabin_asm.S rabin.cpp  Page.cpp CreateCluster.cpp XMLDataParser.cpp  main.cpp -o gen_cluster $(PARSER_FLAG)
	$(CC) $(CFLAGS) convert.cpp -o convert

clean:
	rm -f gen_cluster convert convert_table.txt log.out ../../phase1/latest.txt ../../phase1/longest.txt
	rm -rf cluster
