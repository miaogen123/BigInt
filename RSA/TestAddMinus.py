#_*_coding=utf-8_*_

#测试加减法
a=None
b=None
a_b=None
aPb=None
count=0
with open("test.txt", "rt") as testAdd:
    for line in testAdd:
        if(count==0):
            a=int(line)
        if(count==1):
            b=int(line)
        if(count==2):
            v=int(line)
            m=abs(a-b)
            assert(m==v)
        if(count==3):
            v=int(line)
            m=a+b
            assert(m==v)
        count=(count+1)%4
print("success")


