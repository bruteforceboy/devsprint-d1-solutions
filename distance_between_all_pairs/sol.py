t = int(input())

while t > 0: 
    n = int(input())
    s = input()
    
    s = ''.join(sorted(s))
    
    tot, pref = sum(ord(c) for c in s), 0
    
    res = 0
    for i in range(n):
        pref += ord(s[i])
        tot -= ord(s[i])
        res += tot - ord(s[i]) * (n - i - 1) + ord(s[i]) * (i + 1) - pref
    
    print(res // 2)
    
    t -= 1