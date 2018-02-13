# Default

This is a sample usage of attempting to run a search on the default dataset, which is embedded into the git repository. This will be more comprehensive than other examples.

## Data:

The data will be available in the data folder in a file named `data.xml`.

Here is a snippet of what the file should look like:
```
<data>
	<version>
		<page>
			<title>Ahmed Kamal</title>
			<content>ahmed kamal may refer to ahmed kamal cricketer born 1977 former bangladeshi cricket ahmed kamal footballer born 1981 egyptian football defender ahmed kamal egyptologist 1851 1923 egypt s first egyptologist and pioneer in his own country</content>
		</page>
		<page>
			<title>Adrien Vachette</title>
			<content>the miraculous medal was designed by adrien vachette adrien jean maximilien vachette 1753 1839 was a french goldsmith best known for the production of ornate gold boxes life and career adrien vachette was born in cauffry and possibly apprenticed with pierre franqois drais who sponsored him for a master s certificate 21 july 1779 he had a shop at place 
```

## Query:
There are two scripts that enable you to run the search: `run_single_query_search.sh` and `run_batch_query_search.sh`.

### Usage with `run_single_query_search.sh`:

Using the single query searcher is the easiest way to run the search. Here is an example query that would be run on the above dataset:
```
./run_single_query_search.sh "miraculous medal" 5
```
Note the usage of quotes for the query. This is pretty much required, as RTP search only supports conjunctive queries (two or more words). The number 5 supplied as the last argument the maximum number of documents you'd like retrieved, which in this case would translate to the top 5 documents.

The output of the search can be found in the `target/final_results.txt` file. Here is what the output should look like:
```
Results for: miracul medal
vid: 61	score: 0.182916
vid: 56	score: 0.182916
vid: 51	score: 0.182916
vid: 16	score: 0.182916
vid: 11	score: 0.182916
vid: 6	score: 0.182916
vid: 1	score: 0.182916
vid: 21	score: 0.182916
vid: 26	score: 0.182916
vid: 31	score: 0.182916
```
Versions are indexed in a global scope starting from 0, so version 1, 6, 11, 16, ... 61 are part of the same document/cluster. We know this because the sample dataset in the repository only has 5 documents. In this case, this means that the first version of the second document will be indexed with vid = 1, the first version of the third document will be indexed with vid = 2, and so on.

Though we specified that we wanted the top 5 documents per query, we received 10 version ids. In this scenario, those 10 versions represent the same document/cluster. Therefore, we received 1 document which had the match and 10 versions of that document.

`The output should consist of up to <top_k> documents and up to 10 versions per document`


### Usage with `run_batch_query_search.sh`:
Using the batch query searcher requires you to supply a file path which will have new-line separated queries. Supplied in the repository is a sample `queries_all.txt` file that is intended to search within the sample dataset in the repository. Here is what the `queries_all.txt` file should look like:
```
alumni stadium
college rugby
```
To run the batch query script type:
```bash
./run_batch_query_search.sh query/queries_all.txt
```

Here is what the `target/final_results.txt` file should look like:
```
Results for: alumni stadium
vid: 64	score: 1.04403
vid: 59	score: 1.04403
vid: 54	score: 1.04403
vid: 44	score: 1.04403
vid: 49	score: 1.04403
vid: 19	score: 1.02778
vid: 14	score: 1.02778
vid: 9	score: 1.02778
vid: 4	score: 1.02778
vid: 24	score: 1.02778
Results for: colleg rugbi
vid: 62	score: 0.300609
vid: 57	score: 0.300609
vid: 52	score: 0.300609
vid: 47	score: 0.300609
vid: 42	score: 0.300609
vid: 37	score: 0.300609
vid: 32	score: 0.300609
vid: 27	score: 0.300609
vid: 22	score: 0.300609
vid: 17	score: 0.300609
```

In this case, we had one document match for each query. Each document had at least 10 versions which matched, which is why we see 10 versions per query.

