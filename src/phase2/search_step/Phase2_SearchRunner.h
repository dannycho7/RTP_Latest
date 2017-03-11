/* This program is used to run the complete phase 2 search 
 * Author: Nimisha Srinivasa
 */

#include <vector>
#include <unordered_map>

#include "../../data_structures/ScoreResult.h"
#include "Phase2_ClusterSearcher.h"

using namespace std;

class Phase2_SearchRunner {
	
public:
	double phase2_duration; // global variable to calculate the actual time taken by Phase 2
	
	Phase2_SearchRunner();
	~Phase2_SearchRunner();
	void run_search(int top_k, string full_query);
	void run_search_again(int top_k, string full_query);

private:
	vector<ScoreResult> final_results;
	unordered_map<int,vector<int>> did_to_vids;
	Phase2_ClusterSearcher* phase2_ClusterSearcherObj;

	void init();
	void re_init();
	vector<ScoreResult> readResultsFile(string filepath);
	unordered_map<int,vector<int>> readConvertTable(string filepath);
	void writeResults(vector<ScoreResult> scoreResults, string filepath);
	void runSearchInCluster(int curr_did, string query);
};