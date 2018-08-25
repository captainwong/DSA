import os
import random

def test():
    for i in range(20):
        f = open(os.path.join(os.getcwd(), str(i)+'.txt'), 'w')
        
        f.write('%d %d\n' % (20, 5))
        for j in range(20):
            n = random.randint(0, 100)
            f.write('%d ' % n)
        f.write('\n')
        
        for j in range(5):
            a = random.randint(0, 100)
            b = random.randint(0, 100)
            while(b < a):
                b = random.randint(0, 100)
            f.write('%d %d\n' % (a, b))
        f.write('\n')
        f.close()





if __name__ == '__main__':
    test()