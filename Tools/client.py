import socket

def test():
    print 'start'
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #s.connect(("127.0.0.1", 10021))
    s.connect(("1.83.124.129", 80))
    s.send("hello\n")
    s.close()
    print 'end'

if __name__ == '__main__':
    test()