import random


fp = r'F:\MOOC\DSA\Alarm\_alarm.txt'

def make_alarm():
    f = open(fp, 'w')
    n = 100
    m = 52
    f.write('%d %d\n' % (n, m))
    
    beg_x = 1
    beg_y = 1
    alarms = []
    for i in range(n):
        alarms.append((beg_x, beg_y))
        f.write('%d %d\n' % (beg_x, beg_y))
        if i % 2 == 0:
            beg_x += 2#random.randint(2, 10)
            beg_y += 1#random.randint(2, 10)
        else:
            beg_x += 1#random.randint(2, 10)
            beg_y += 2#random.randint(2, 10)
    
    beg_x /= 2
    beg_y /= 2
    points = []
    for i in range(m):
        #x = random.randint(0, beg_x)
        #y = random.randint(0, beg_y)
        x = i
        y = i
        points.append((x, y))
        f.write('%d %d\n' % (x, y))
    
    f.close()
    
    

def check_alarm():
    f = open(fp)
#     data = ''
#     temp = f.read(1024)
#     while temp is not None:
#         data += temp
#         temp = f.read(1024)
        
    lines = f.readlines()
    f.close()
    (n, m) = lines[0].split()
    
    n = int(n)
    m = int(m)
    alarms = []
    points = []
    for i in range(n):
        (x, y) = lines[i+1].split()
        x = int(x)
        y = int(y)
        alarms.append((x, y))
    for i in range(m):
        (x, y) = lines[i+n+1].split()
        x = int(x)
        y = int(y)
        points.append((x, y))
    
    def get_side(xa, yb, px, py):
        return px * py - (xa - px) * (yb - py)
    
    def get_range(px, py):
        rank = 1
        a = alarms[0]
        ret = get_side(a[0], a[1], px, py)
        if ret > 0: # right
            for a in alarms[1:]:
                rank += 1
                ret = get_side(a[0], a[1], px, py)
                if ret == 0:
                    return rank
                elif ret < 0:
                    return rank - 1
                
            return rank
        elif ret == 0:
            return rank
        else:   # left
            return 0
                
    for p in points:
        r = get_range(p[0], p[1])
        print r


if __name__ == '__main__':
    make_alarm()
    #check_alarm()
    
    