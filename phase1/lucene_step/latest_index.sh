rm -rf index
if [ $1 -eq 1 ]; then
	time java -jar archive_lucene_index2.jar ../latest.txt
elif [ $1 -eq "2" ]; then
	time java -jar archive_lucene_index2.jar ../longest.txt
fi
