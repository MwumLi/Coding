#coding=utf-8
#This is a example , which is used to show str's usage

#Use len() to caculate the length
s = "This is string"
print "str's length : "+str(len(s))
print ""

#use str.count(sub,[,start[,end]] to count the number of occurrences of substring sub in  string str[start:end] 
a = s.count("i",2,5)
b = s.count("i",2,6)
print "The number of 'i' is :\n"+str(a)+" bwtween 2 and 5 and \n"+str(b)+" between 2 and 6 in "+s
print ""

# Use str.find(sub, [,start [,end]]) to find the position of the first occurence of substring sub  in string str
a = s.find("i", 5)
print "The first occurence of substring 'i' is "+str(a)+" in string '"+s+"' from  5 to end"
print ""

# Use str.replace(old, new [, count]) to replace all occurrences of substring old in string str by substring new
# In fact, this function generate a new string, rather than  modifying the  original string
# The number of replacementcan be specified
a = s.replace("i", "modify", 2)
print "The new string is '"+a+"' after replaceing 'i' in '"+s+"' by 'modify'"
print "" 

#Use str.split([sep [, count]]) to split the string str into count+1 substring by sepeater sep
a = s.split("i", 2)
print a
print 

#Use str.capitalize() to capitalize the first character of the string str
i = 0
for b in a:
    a[i]=b.capitalize()
    i+=1
print a
print ""
#Use str.join(iterable) to concate the items in the iterable with str as  spparator

a=("df",'d',"sd")
b="@".join(a)
print b
print ""
# Use str.strip([chars]) to delete whitespace or chars with leading and trailing in str
# Use str.lstrip([chars]) to delete whitespace or chars with leading in str
# Use str.rstrip([chars]) to delete whitespace or chars with trailing in str
s="  woaini "
print s.strip()
print s.lstrip('  w')
print s.rstrip('i ')
