#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdlib.h>

#include "Page.h"
#include "ReuseTableInfo.h"
#include "neverlost_util.h"
#include "RepresentativeChoice.h"

using namespace std;

class CreateCluster{
public:
	unordered_map<string,int> title_to_did;
	unordered_map<int,vector<int>> did_to_vids;
	int doc_num;

	int total_found_fragment;
	int did, next_did; // document id
	int vid, next_vid; // version id
	int fid, next_fid; // fragment id
	unordered_map<string, int> title_did_hash; // hash from title to document id
	unordered_map<int, int> vid_did_hash; // hash from vid to did
	unordered_map<int, vector<int>> did_vid_hash; // hash from did to vid; each document will have a vector of vid
	unordered_map<int, int> fid_size_hash; // hash from fid to its size
	unordered_map<int, string> fid_content_hash; // hash from fid to its content
	unordered_map<string, int> content_fid_hash; // hash from a fragment's content to its id
	unordered_map<int, vector<int>> vid_fid_hash; // hash from vid to fid; each page will have a vector of fragment
	unordered_map<int ,string> did_title_hash; // hash from did to title 
	unordered_map<int, vector<ReuseTableInfo>> frag_reuse_table;
	RepresentativeChoice choice;
	ofstream representative_version;	//could be latest or longest depending on users input

	CreateCluster();
	void init();
	void deal_with_ver(Page* page);
	void cluster_init();
	int get_did_from_title(string &title);
	void maintain_did_vid_hash();
	int get_words_number(string &line);
	void output_fragment(int fid, string &line, string& folder_base);
	void deal_with_title(string title, int pageno);
	void do_fragments(vector<string>& frag, int pageno, string& folder_base);
	void do_page(vector<string>& frag, int pageno, string& folder_base);
	char hash_string(string s);
	void hash_content(char *result_hash, vector<string>& v);
	void deal_with_doc(string& content, int doc_id, string& folder_base);
	void output_index(string& folder_base);
	void output_dvrelation(string& folder_base);
	void gen_index_for_cluster(string& folder_base);
	int output_convert_table();
	void gen_index_for_all_cluster();
};