#coding=utf-8
#此例展示面向过程的编程思想  
#构建一个Dog和Animal类 
#Dog继承Animal

print "Object-Oriented Programming"
class Animal:
    ''' This is class Animal
    '''
    def __init__(a, atype):
        '''Thi is Animal __init__
        '''
        if atype != "":
            a.atype=atype
        else:
            a.atype="Animal"
class Dog(Animal):
    '''This is class Dog
    
    '''
    dog_num = 0
    def __init__(self, name):
        ''' This is dog __init__
        
        '''
        Animal.__init__(self, "dog")
        if name != "":
            self.name=name
        else:
            self.name=""
        self.dog_num += 1
        self._hh = "string"

    def desc(self):
        '''This is dog __desc
        
        '''
        if(self.name != ""):
            print "The "+self.atype+"'s name is "+self.name
        else:
            print "The "+self.atype+" has no name"
    
dog = Dog("Tom")
zz = Animal("");
#dog.desc()
print type(dog)
print type(zz)

