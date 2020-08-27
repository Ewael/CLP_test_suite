#!/usr/bin/env python3

patterns = open("patterns", 'r')
charset = "septhuionz"
table = {'s': '1', 'e': '2', 'p': '3', 't': '4', 'h': '5',
         'u': '6', 'i': '7', 'o': '8', 'n': '9', 'z': '0'}
debug = 0
loop = 0
size = 3628800

for pattern in patterns:

    # update table
    pattern = pattern[:-1]
    i = 0
    for l in charset:
        table[l] = pattern[i]
        i += 1

    # compute
    sept = ''.join(table[a] for a in "sept")
    huit = ''.join(table[a] for a in "huit")
    onze = ''.join(table[a] for a in "onze")
    res = int(sept) + int(huit)

    # output and check
    if debug:
        print("-----------------------------")
        print("pattern = {}".format(pattern))
        print("table = {}".format(table))
        print("  " + ' '.join(sept))
        print("+ " + ' '.join(huit))
        print("= " + ' '.join(str(res)))
        print("onze = " + ' '.join(onze))
    else:
        loop += 1
        print("[+] Testing... {:.2f}% completed".format((loop/size)*100))
    if res == int(onze):
        print("[x] Success!\n")
        print("** table: \n{}\n".format(table))
        print("** operation:")
        print("  " + ' '.join(sept))
        print("+ " + ' '.join(huit))
        print("= " + ' '.join(str(res)) + '\n')
        break

print("[-] Bruteforce over")
