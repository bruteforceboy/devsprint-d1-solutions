t = int(input())
while t > 0: 
    n = int(input())
    s = input()
    freq = [0] * 26
    for i in range(n):
        freq[ord(s[i]) - ord('a')] += 1
    odd = 0
    for i in range(26):
        if freq[i] & 1: 
            odd += 1
    print(max(0, odd - 1))
    t -= 1