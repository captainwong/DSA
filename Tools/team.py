import random
total = 4
def team():
    A = []
    B = []
    C = []
    f = open(r'F:\MOOC\DSA\Team\team.txt', 'w')
    print '%d' % total
    f.write('%d\n' % total)
    out = ''
    while len(A) != total:
        i = random.randint(1, total)
        if i not in A:
            A.append(i)
            f.write('%d ' % i)
            out += '%d ' % i        
    print out
    f.write('\n')
    
    out = ''
    while len(B) != total:
        i = random.randint(1, total)
        if i not in B:
            B.append(i)
            f.write('%d ' % i)
            out += '%d ' % i        
    print out
    f.write('\n')        
    
    out = ''
    while len(C) != total:
        i = random.randint(1, total)
        if i not in C:
            C.append(i)
            f.write('%d ' % i)
            out += '%d ' % i        
    print out
    f.write('\n')
    
    k = random.randint(1, total)
    f.write('%d\n' % k)
    print k
    f.close()

    members = {}
    for i in range(total+1):
        members[i] = False
        
    A.reverse()
    B.reverse()
    C.reverse()
    
    flag = 0
    for i in range(total):
        if flag % 3 == 0:
            while len(A) > 0:
                a = A.pop()
                if members[a] == False:
                    members[a] = True
                    if a == k:
                        print 'A'
                        return
                    break
        elif flag % 3 == 1:
            while len(B) > 0:
                b = B.pop()
                if members[b] == False:
                    members[b] = True
                    if b == k:
                        print 'B'
                        return
                    break
        else:
            while len(C) > 0:
                c = C.pop()
                if members[c] == False:
                    members[c] = True
                    if c == k:
                        print 'C'
                        return
                    break
                    
        flag += 1
        

if __name__ == '__main__':
    team()