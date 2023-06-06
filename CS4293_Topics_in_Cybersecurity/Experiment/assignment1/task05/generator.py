with open("1000bytes2.txt", "w") as file:
    for i in range(0, 1000):
        file.write(str(i%10))
