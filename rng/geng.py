for i in range(121422000, 122422081):
    for j in range(2, i // 2):
        if i % j == 0: break
    else: print(i - 2421999, i)

