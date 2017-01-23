echo $1
rm -rf search_frag.txt
cp ../../lucene_step/index_search ./
./index_search --index index --no-features --postings <<< $1
rm -rf index_search
