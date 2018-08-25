import os
from subprocess import Popen, PIPE
import sys

def test_range():
    target = os.path.join(os.getcwd(), 'a.out')
    for i in range(20):
        print '#%d' % i
        f = os.path.join(os.getcwd(), str(i)+'.txt')
        cmd = '%s < %s' % (target, f)
        process = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE)

        # Poll process for new output until finished
        while True:
            nextline = process.stdout.readline()
            if nextline == '' and process.poll() != None:
                break
            sys.stdout.write(nextline)
            sys.stdout.flush()
            nextline = nextline.strip('\n')
            if len(nextline) == 0:
                continue
            
    
        output = process.communicate()[0]
        exitCode = process.returncode
    
        if (exitCode == 0):
            print 'ok'
            #print 'output is', output
        else:
            print 'ExitCode Error:', (exitCode, output)





if __name__ == '__main__':
    test_range()