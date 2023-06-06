import math
def mod_pow(a, p, n):  
    res_str = "( 1"  
    res_val = 1
    p_bin = str(bin(p))
    z = a
    for i in range(len(p_bin[2:])):
        if i == 0:
            z = a
            print("%d^(2^%d) mod %d = %d"%(a, i, n, z))
        else:
            x = (z**2)%n
            print("%d^(2^%d) mod %d = %d^2 mod %d = %d"%(a, i, n, z, n, x))
            z = x
        if p_bin[-i-1] is '1':
            res_str = res_str + " * %d"%(z)
            res_val = (res_val * z)%n
    print(res_str+" ) mod %d = %d"%(n, res_val))

mod_pow(47, 19, 71)
