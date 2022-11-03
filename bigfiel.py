with open("bbc.txt", 'w+') as file:
    for i in range(1449608, 2760329):
        file.write(str(i))
        file.write(" ")
    file.close()
