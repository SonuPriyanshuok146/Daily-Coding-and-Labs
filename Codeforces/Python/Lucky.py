t = int(input())

for _ in range(t):
    str = input()
    temp = int(str)
    ans = 0
    
    for i in range(0, 6):
        r = temp%10
        if i < 3:
            ans += r
        else:
            ans -= r
        temp //= 10
        
    if(ans == 0):
        print("YES")
    else:
        print("NO")
    