#include <string>
#include <vector>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <ctime>
#include <sys/time.h>

#include "../../data_structures/ReuseTableInfo.h"
#include "../../data_structures/Fid_Occurence.h"
#include "../../data_structures/R_Occurence.h"
#include "../../data_structures/V_Occurence.h"
#include "../../data_structures/ScoreResult.h"

class Phase2_Searcher{
public:
	int query_len;

	void init();
	void read_index();
    void read_search_frag();
    void intersection();
    void scoring();

private:
	unordered_map<int, vector<ReuseTableInfo>> frag_reuse_table;
	vector<vector<Fid_Occurence>> search_frag; // <<fID, <pos>>>
	unordered_map<int ,int> vid_titlelen_hash; // vid to title length
	unordered_map<int, vector<set<int>>> intersection_hash; // this keeps the intersection results
	vector<R_Occurence> result_posting; // this keeps the result posting after intersection
	vector<ScoreResult> score_result; // this vector keeps the final scoring results

	clock_t start;  // global variable added to mark the starting point of time statistics
	double duration;  // global variable added to calculate non-I/O time

	void score_page(int vid, vector<set<int>> &occur_terms);
	void cal_min_span_title(int &min_span, int vid, vector<set<int>> &occur_terms, int term_number, int title_len);
	void cal_min_span(int &min_span, int vid, vector<set<int>> &occur_terms, int term_number);
	int body_tf(int vid, vector<set<int>> &occur_terms, int term_number);
	void print_vid();
	void intersection1();
};
