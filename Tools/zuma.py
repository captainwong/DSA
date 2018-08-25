import os
import random

def zuma():
    f = open(os.path.join(os.getcwd(), 'zuma.txt'), 'w')
        
    for i in range(10):
        c = random.randint(ord('A'), ord('C'))
        f.write('%c' % c)
    f.write('\n')
    f.write('50\n')
    for i in range(50):
        K = random.randint(0, 10)
        C = random.randint(ord('A'), ord('C'))
        f.write('%d %c\n' % (K, C))
    f.close()
    
    
if __name__ == '__main__':
    zuma()