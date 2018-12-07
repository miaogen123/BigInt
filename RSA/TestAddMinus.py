#_*_coding=utf-8_*_

def TestAddMinus(filename):
    #测试加减法
    a=None
    b=None
    count=0
    gCount=0
    with open(filename, "rt") as testAdd:
        for line in testAdd:
            if(count==0):
                a=int(line)
            if(count==1):
                b=int(line)
            if(count==2):
                v=int(line)
                m=(a-b)
                if(m!=v):
                    print(gCount)
                    #assert(False)
            if(count==3):
                v=int(line)
                m=a+b
                if(m!=v):
                    print(gCount)
                    #assert(False)

            count=(count+1)%4
            gCount+=1
    print("success")

def TestMulti(filename):

    a=None
    b=None
    count=0
    gCount=0
    with open(filename, "rt") as testAdd:
        for line in testAdd:
            if(count==0):
                a=int(line)
            if(count==1):
                b=int(line)
            if(count==2):
                v=int(line)
                m=(a*b)
                if(m!=v):
                    print(gCount)
                    #assert(False)
            count=(count+1)%3
            gCount+=1
    print("success")
    pass

if __name__=="__main__":
    #TestAddMinus("test.txt")
    TestMulti("testMulti.txt");
