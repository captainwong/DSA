
total = 100000
def company():
    f = open(r'F:\MOOC\DSA\Company\company.txt', 'w')
    f.write('%d %d\n' % (total, total * 2 + 1))
    for n in range(total):
        f.write('I %d 12\n' % n)
        f.write('C\n')
    f.write('N\n')
    f.close()



if __name__ == '__main__':
    company()