f = open("mapping.txt", "r")
txt = f.readlines()
f.close()
org_perm = [chr(int("0x" + t.strip()[:2], 0)) for t in txt]

perm = dict()
for i in range(ord(" "), ord("~") + 1):
    perm[org_perm[i - ord(" ")]] = chr(i)

inp = input()
for c in inp:
    print(perm[c],end="")
 