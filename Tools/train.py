import random
#from subprocess import Popen, PIPE
import subprocess
import sys


test_data = r'F:\MOOC\DSA\Train\train.txt'
correct_answer = r'F:\MOOC\DSA\Train\_ca.txt'
compute_answer = r'F:\MOOC\DSA\Train\_ca2.txt'

def train():
    n = 500
    m = 500
    f = open(test_data, 'w')
    f.write('%d %d\n' %(n, m))
    print n, m
    B = []
    out = ''
    for i in range(n):
        B.append(i+1)
#         a = 1
#         while a in B:
#             a = random.randint(1, n)
#         f.write('%d ' % a)
#         B.append(a)
#         out += '%d ' % a
    #B = [1, 2, 3, 5, 4]
    
    for i in range(1):
        i = random.randint(2, n/2)
        j = i + random.randint(1, n/2 -1)
        o = B[i]
        B[i] = B[j]
        B[j] = o
    
    print B
    
    for b in B:
        f.write('%d ' % b)
    f.write('\n')
    f.close()
    B.reverse()
    
    
    S = []
    OP = []
    i = 1
    #St = 0
    for k in range(n):
        Bk = B.pop()
        while len(S) == 0 or Bk != S[-1]:
            if i > n or len(S) == m:
                print 'No'
                return False
            #St = i
            
            S.append(i)
            i += 1
            OP.append('push\n')
            
        if len(S) == 0 or Bk != S[-1]:
            print 'No'
            return False
        
        S.pop()
        OP.append('pop\n')

    if len(S) != 0:
        print 'No'
        return False
    
    f = open(correct_answer, 'w')
    for o in OP:
        f.write(o)
        print o.strip()
    f.close()
    
    return True

def test_train():# 
    cmd = '%s < %s > %s' % (r'F:\MOOC\DSA\Debug\train.exe', test_data, compute_answer)
    print cmd
    #cmd = tuple(cmd.split())
    #print cmd
    p = subprocess.Popen(cmd, shell=True)
    p.communicate()
    exitCode = p.returncode

    if (exitCode == 0):
        print 'return 0'
        #print 'output is', output
    else:
        print 'ExitCode Error:', (exitCode)
        
    f = open(correct_answer)
    correct_data = ''
    data = f.read(1024)
    while data:
        correct_data += data
        data = f.read(1024)
    f.close()
    
    f = open(compute_answer)
    compute_data = ''
    data = f.read(1024)
    while data:
        compute_data += data
        data = f.read(1024)
    f.close()
    
    if cmp(correct_data, compute_data) != 0:
        print 'Failed!'
    else:
        print 'Success!'

if __name__ == '__main__':
    while train() is False:
        pass
    
    test_train()
    
    
    