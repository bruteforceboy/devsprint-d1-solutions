t = int(input())
while t > 0:
    n = int(input())
    arr = [int(x) for x in input().split()]
    print(sum(arr))
    t -= 1