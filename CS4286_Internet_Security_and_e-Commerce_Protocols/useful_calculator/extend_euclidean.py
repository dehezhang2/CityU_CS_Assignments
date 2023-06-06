import math
def exGcd(a, b):
    if b==0:
        return (a, 1, 0)
    if a < b:
        return exGcd(b, a)
    print("euc: %d = %d*%d+%d"%(a, b, math.floor(a/b), a%b))
    (r, x, y) = exGcd(b, a%b)
    print("eeuc: 1 = (%d)(%d)+(%d)(%d)"%(b, x, a%b, y))
    return (r, y, x - math.floor(a/b)*y)

a = 9
b = 71
(r,x,y) = exGcd(a, b)
print("eeuc: 1 = (%d)(%d)+(%d)(%d)"%(a if a>b else b, x, b if a>b else a, y))
