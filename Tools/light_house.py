def printn(n):
    s = 0
    for i in range(n):
        s += i
    print s

def light_house():
    f = open(r'F:\MOOC\DSA\LightHouse\light_house.txt', 'w')
    total = 123
    printn(total)
    f.write('%d\n' % total)
    l = range(total)
    l.reverse()
    for i in l:
        f.write('%d %d\n' % (i, i))
    f.close()
    
    
if __name__ == '__main__':
    light_house()