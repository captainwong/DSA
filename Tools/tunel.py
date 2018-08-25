import random


def test_tunel():
    f = open(r'F:\MOOC\DSA\THUPA2_4_Queap\_queap.txt', 'w')
    total = 10
    tunel = []
    print total
    f.write('%d\n' % total)
    opch = ['E', 'D', 'M']
    i = 0
    while True:
        if i == total:
            break
        op = random.randint(0, 2)
        if op == 0:
            x = random.randint(0, 100)
            tunel.append(x)
            out = '%c %d\n' % (opch[op], x)
            f.write(out)
            #print out.strip()
            i += 1
        elif op == 1:
            if len(tunel) == 0:
                continue
            out = tunel[0]
            tunel = tunel[1:]
            print out
            f.write('%c\n' % opch[op])
            i += 1
        elif op == 2:
            if len(tunel) == 0:
                continue
            m = tunel[0]
            for t in tunel: 
                if m > t:
                    m = t
            out = '%d' % m
            f.write('M\n')
            print out
            i += 1
    f.close()













if __name__ == '__main__':
    test_tunel()







