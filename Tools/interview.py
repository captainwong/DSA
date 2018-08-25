import random
n = 100
m = 5
def interview():
    f = open(r'F:\MOOC\DSA\Interview\interview.txt', 'w')
    f.write("%d %d\n" % (n, m))
    for i in range(n):
        f.write("%d " % i)
    f.write("\n")
    f.close()



if __name__ == '__main__':
    interview()