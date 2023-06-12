f = open("mapping.txt", "r")
txt = f.readlines()
f.close()
org_perm = [chr(int("0x" + t.strip()[:2], 0)) for t in txt]


perm = dict()
printable = [chr(c) for c in range(ord(" "), ord("~") + 1)]
printable_len = len(printable)
#print(printable)
#print(org_perm)
for i in range(ord(" "), ord("~") + 1):
    perm[org_perm[i - ord(" ")]] = chr(i)
#print(perm)


inp = input()
for c in inp:
    print(perm[c],end="")
 