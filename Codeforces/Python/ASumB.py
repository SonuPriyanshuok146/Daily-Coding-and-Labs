t = int(input())

for _ in range(t):
    n = int(input())
    r = n%10
    n //= 10
    print(r+n%10)