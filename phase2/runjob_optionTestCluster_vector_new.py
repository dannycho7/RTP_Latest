#!/usr/bin/python
import os
import sys

# function to run shell command
def run_command(com):
    output = os.popen(com).read()
    a = output.split('\n')
    for b in a:
        print b

def mycmp(a,b):
    if (a[1]>b[1]):
        return -1
    if (a[1]<b[1]):
        return 1
    return 0

if len(sys.argv) != 4:
    print "needed query, query length and top k!"
    exit()

query = sys.argv[1]
query_len = int(sys.argv[2])
fin = open('../phase1_latest/search_doc/vidlist.txt', 'r')# !!!USER!!!use phase 1's result, need to modify     input file path
k=int(sys.argv[3])

line = fin.readline()
fin.close()
vd_list = line.rstrip('\n').split(' ')
vd_list.remove('') # vd_list contains the vid from phase1_rep
            
# create dictionary 'dic_dv' for the relation from did to number of vid in its cluster
fin_dv = open('./create_clusters/convert_table.txt', 'r')
lines_dv = fin_dv.readlines()
fin_dv.close()
dic_dv = {}
for i in range(len(lines_dv)):
    line_dv_list = lines_dv[i].rstrip('\n').split(' ')
    key_dv = line_dv_list[0]
    value_dv = int(line_dv_list[1]);
    dic_dv[int(key_dv)] = value_dv
    
# choose p vids which occupy k vids to compare with optionTest
count=0
final_vid_list=[]
fout = open('vidlistC.txt', 'w')
for p in range(len(vd_list)):
    final_vid_list.append(vd_list[p]) # add one more vid into the list
    did = int(vd_list[p])
    count = count + dic_dv[did]
    # work on cluster did
    print 'work on cluster', did, ':'
    fout.write(str(did)+'\n')
    
    os.chdir('cluster/'+str(did))
    print '**********enter cluster '+str(did)+'**********'
    # lucene search to generate "search_frag.txt"
    com = '../../lucene_step/run_search_qinghao.sh "'+query+'"'
    #com = '../../lucene_step/index_search --index index --no-features --postings <<< "housing office"'
    print 'run lucene search:'
    run_command(com)
    # search_doc to generate "vidlist.txt"
    com = '../../search_doc/search_doc '+ str(query_len)
    print 'run search_doc:'
    run_command(com)
    # run option C using "search_frag.txt", "vidlist.txt" and "forward.txt"
    com = '../../search_doc/optionTestCluster_vector '+ str(query_len)
    print 'run optionTestCluster:'
    run_command(com)
    # finally, quit this cluster
    os.chdir('../..')
    
    if count > k:
        print 'p=', p
        break
if count < k :
    print 'vidlist.txt does not contain enough pages to calculate top ', k
    print count, p+1
fout.close()
