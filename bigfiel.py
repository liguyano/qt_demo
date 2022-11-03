with open("bbc.txt", 'w+') as file:
    for i in range(10000000):
        file.write(str(i))
        file.write(" ")
    file.close()
