"""
Quadruple Table
"""
import pandas as pd

#--------------- take input postfic string where each token seperated by ,
post_str = input("Enter post fix string as , seperater tokens:-> ")

#--------------- convert string ti list
str_list = post_str.split(',')

#---------------make list of operator
op_list = ['+','-','*','/','%','^']

#---------------  make empty quadruple table
q_tab = pd.DataFrame(columns=['operator','arg-1','arg-2','result'])

#--------------- find length of list
l = len(str_list)

#--------------- initialize index in table by 0
j = 0

#--------------- initialize temporary variable index by 0
temp = 1

#--------------- initialize pointer in list by 0
i = 0

#--------------- process till length of string is >1
while l>1:
    
    #--------------- operator at current index
    if str_list[i] in op_list:
        op = str_list[i]        # get operator from i index
        a2 = str_list[i-1]      # get right operand (arg-2) from i-1 index
        a1 = str_list[i-2]      # get left operand (arg-1) from i-2 index
        r = 't'+ str(temp)      # resulr in new temporary
        temp += 1               # increment temp index
        q_tab.loc[j] = [op,a1,a2,r]     # make entry in table at index j
        j += 1                  # increment table index by 1
        str_list[i] = r         # put result in list at operator place
        str_list.remove(a1)     # remove arg-1 from list
        str_list.remove(a2)     # remove arg-2 from list
        i -= 2                  # list index decrement by 2 as 2 elements removed from list
        l = len(str_list)       # redefine list length
    
    #--------------- assignment operator at current index
    elif str_list[i] == '=':
        a1 = str_list[i-1]      # ger right operand (arg-1) from index i-1
        r = str_list[i-2]       # ger result from index i-2
        q_tab.loc[j] = ['=',a1,'',r]    # make entry in table
        j += 1                  # increment table index by 1
        del str_list[i]         # delete '=' from list
        str_list.remove(a1)     # remove arg-1 from list
        i -= 2                  # list index decrement by 2 as 2 elements removed from list
        l = len(str_list)       # redefine list length
    
    #--------------- operand fields in list
    else:
        i += 1                  # just increment index by 1 to get next element        

#--------------- print table
print(q_tab)