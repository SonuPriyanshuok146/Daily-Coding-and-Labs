t = int(input())
events = list(map(int, input().split()))

officier = 0
untreated = 0

for x in events:
    
    if x == -1:
        if officier > 0:
            officier -= 1
        else:
            untreated += 1
    else:
        officier += x
        
print(untreated)