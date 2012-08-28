import shutil

ufile = open('prob_list.in');

while True:
    line = ufile.readline()
    if not line: break

    chapter, num = line.split()
    num = int(num)

    for i in range(num):
        line = ufile.readline()
        shutil.move(line[:-1], chapter)
    
