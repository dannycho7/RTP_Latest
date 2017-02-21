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
fin = open('../phase1_super/search_doc/result.txt', 'r')# !!!USER!!!use phase 1's result, need to modify     input file path
k=int(sys.argv[3])
lines = fin.readlines()
fin.close()
if (k>len(lines)):
    print 'not enough lines, k<result length, set k to be ',len(lines)
    k = len(lines)

# create dictionary 'dic_dv' for the relation from did to number of vid in its cluster
fin_dv = open('convert_table.txt', 'r')
lines_dv = fin_dv.readlines()
fin_dv.close()
dic_dv = {}
for i in range(len(lines_dv)):
    line_dv_list = lines_dv[i].rstrip('\n').split(' ')
    key_dv = int(line_dv_list[0])
    value_dv = []
    for j in range(int(line_dv_list[1])):
        value_dv.append(int(line_dv_list[2+j]))
    dic_dv[key_dv] = value_dv
    
# choose p vids which occupy k vids to compare with optionTest
final_result = []

for p in range(k):
    line_list = lines[p].rstrip('\n').split(' ')
    did = int(line_list[0])
    # work on cluster did
    print 'work on cluster', did, ':'
    
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
    fr = open('result.txt', 'r')
    lines_r = fr.readlines()
    fr.close()
    for i in range(len(lines_r)):
        lines_r_list = lines_r[i].rstrip('\n').split(' ')
        rid = int(lines_r_list[0])
        rscore = float(lines_r_list[1])
        rvid = dic_dv[did][rid]
        final_result.append((rvid, rscore))
    # finally, quit this cluster
    os.chdir('../..')

final_result.sort(cmp=mycmp)
fout=open('final_result.txt', 'w')
for item in final_result:
    fout.write(str(item[0])+' '+str(item[1])+'\n')
fout.close()


