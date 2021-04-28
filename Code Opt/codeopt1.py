import pandas as pd
a=pd.read_csv("input.csv")
c=a.shape
print(a)
b=[]
for i in range(c[0]):
    for j in range(i+1,c[0]):
        if(a['right'][i]==a['right'][j]):
            for d in range(c[0]):
                b=b+[(len(a['right'][d]))]
                for z in range(b[d]):
                    if(a['right'][d][z]==a['left'][j]):
                        x=list(a['right'][d])
                        x[z]=a['left'][i]
                        l=''.join(x)
                        a['right'][d]=a['right'][d].replace(a['left'][j],a['left'][i])
            a['left'][j]=a['left'][i]
df=pd.DataFrame(a)
df.to_csv('output1.csv',index=False)
p=pd.read_csv("output1.csv")
print("After checking and putting the value of common exepression ")
print(p)
i=0
j=i+1
while(j<c[0]):
    if(p['right'][i]==p['right'][j]):
        if(p['left'][i]==p['left'][j]):
            p.drop([j],axis=0,inplace=True)
            i+=2
            j+=1
        else:
            i+=1
    j+=1
    if(j==c[0]):
        i=i+1
        j=i+1
    if(i==c[0]):
        j=c[0]
print("After elemenating the common expression")
df=pd.DataFrame(p)
df.to_csv('output1.csv',index=False)
p=pd.read_csv("output1.csv")
print(p)
c=p.shape
#print(c)
count=0
i=0
j=0
h=1
while(j<c[0] and i<c[0]):
    b=[]
    b=b+[(len(p['right'][j]))]
    for z in range(b[0]):
        #print(z,j,i)
        if(p['right'][j][z]==p['left'][i]):
            count=1
    j+=1
    #print(j)
    #print(c[0])
    if(j==c[0]):
        #print(count)
        if(count!=1):
            p.drop([i],axis=0,inplace=True)
            df=pd.DataFrame(p)
            df.to_csv('output1.csv',index=False)
            p=pd.read_csv("output1.csv")
            3#print(p)
            c=p.shape
            print(c)
        i+=1
        j=0
print("After dead code elimination")
print(p)
df=pd.DataFrame(p)
df.to_csv('output1.csv',index=False)
p=pd.read_csv("output1.csv")
c=p.shape
print("The final optimized code is....")
for i in range(c[0]):
    print(str(p['left'][i])+"="+str(p['right'][i]))
