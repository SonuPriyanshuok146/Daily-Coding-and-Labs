n , k = map(int, input().split())
timeleft = 240 - k
solved = 0
timespent = 0

for i in range(1, n+1):
    timespent += 5*i
    
    if timespent <= timeleft:
        solved += 1
    else:
        break
print(solved)