"""
LL(1) grammar
"""
#import library
import re
import pandas as pd

#---------------function to calculate first set---------------
def first(x):
    
    nt_prod = []
    first_set = []
    
    for i in range(no_prod):
        if prod[i][0] == x:
            nt_prod = prod[i].split("->")
            nt_prod = nt_prod[1]
            first_set += nt_prod[0];

    first_set.sort()
            
    return first_set

#---------------function to calculate follow set---------------
def follow(x):
    
    follow_set = []
    
    if x == nt[0]:
        follow_set += '$';
        
    for i in range(no_prod):
        index_x = prod[i].find(x,3) 
        if index_x != -1:
            if index_x == len(prod[i])-1:
                if x != prod[i][0]:
                    follow_set += prod[i][0]
            else:
                next_ele = prod[i][index_x+1]
                if re.match(r'[^A-Z]',next_ele):
                    follow_set += next_ele
                else:
                    follow_set += nt_first_set[next_ele]
                    if '^' in follow_set:
                        follow_set.remove('^')
                        follow_set += prod[i][0]

    follow_set = list(set(follow_set))
    follow_set.sort()
    
    return follow_set


#---------------take grammar input from file---------------
text_file = open("grammar.txt","r")
grammar = text_file.read()

#---------------make list of productions---------------
prod = grammar.split('\n')

#---------------count number of productions---------------
no_prod = len(prod)

#---------------empty list of non-terminals---------------
nt = []

#---------------empty list of terminals---------------
t = []

#---------------make list of non-terminals and terminals---------------
for i in range(no_prod):
    l = len(prod[i])
    if prod[i][0] not in nt:
        nt += prod[i][0]
    for j in range(3,l):
        if re.match(r'[^A-Z]',prod[i][j]) and (prod[i][j] not in t):
            t += prod[i][j]
    
#---------------remove ^ rom terminal list---------------
if '^' in t:
    t.remove("^")

#---------------add $ in terminal list---------------
t+='$'
     
#---------------empty dictionary of first set---------------
nt_first_set = pd.Series('', index = nt)

#---------------find first set of non-termibnal---------------
for one_nt in nt:
    one_nt_first = first(one_nt)
    nt_first_set[one_nt] = one_nt_first
    
#---------------replace each non-terminal in first set with its fisrt set---------------
change = 1
while change == 1:
    change = 0
    for one_nt in nt:
        for each_first in nt_first_set[one_nt]:
            if re.match(r'[A-Z]',each_first):
                nt_first_set[one_nt].remove(each_first)
                nt_first_set[one_nt] += nt_first_set[each_first]
                change = 1
                
#---------------remove redundant element form follow set---------------
for one_nt in nt:
    nt_first_set[one_nt] = list(set(nt_first_set[one_nt]))
    nt_first_set[one_nt].sort()
    
#---------------print first set---------------
print('-----First set-----')
print(nt_first_set)

#---------------empty dictionary of follow set---------------
nt_follow_set = pd.Series('', index = nt)
    
#---------------find and print follow set of non-terminal---------------
for one_nt in nt:
    one_nt_follow = follow(one_nt)
    nt_follow_set[one_nt] = one_nt_follow

#---------------replace each non-terminal in follow set with its follow set---------------
change = 1
while change == 1:
    change = 0
    for one_nt in nt:
        for each_follow in nt_follow_set[one_nt]:
            if re.match(r'[A-Z]',each_follow):
                if each_follow != one_nt:
                    nt_follow_set[one_nt] += nt_follow_set[each_follow]
                nt_follow_set[one_nt].remove(each_follow)
                change = 1

#---------------remove redundant element form follow set---------------
for one_nt in nt:
    nt_follow_set[one_nt] = list(set(nt_follow_set[one_nt]))
    nt_follow_set[one_nt].sort()
                
#---------------print follow set---------------
print('-----Follow set-----')
print(nt_follow_set)

#---------------make predictive parsing table(ppt)---------------
ppt = pd.DataFrame('',columns=t,index=nt)

#---------------initialize ppt with empty list---------------
for r in nt:
    for c in t:
        ppt.at[r,c] = []  

#---------------construct ppt---------------
for one_nt in nt:
    for i in range(no_prod):
        nt_prod = prod[i].split("->")
        if nt_prod[0] == one_nt:
            nt_prod = nt_prod[1]
            if re.match(r'[^A-Z]',nt_prod[0]):
                if nt_prod[0] != '^':
                    ppt.at[one_nt,nt_prod[0]].append(nt_prod)
                else:
                    for each_follow in nt_follow_set[one_nt]:
                        ppt.at[one_nt,each_follow].append('^')
            else:
                for each_ele in nt_first_set[nt_prod[0]]:
                    if each_ele != '^':
                        ppt.at[one_nt,each_ele].append(nt_prod)
                        
            
#---------------print ppt---------------
print('-----Predicative Parsing Tabel-----')
print(ppt)

#---------------check for LL(1)---------------
ll1 = 1
for r in nt:
    for c in t:
        if len(ppt.at[r,c]) > 1:
            ll1 = 0
            break

if ll1:
    print('***** Grammar is LL(1) *****')
else:
    print('***** Grammar is not LL(1) *****')