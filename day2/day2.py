f = open("day2.txt", "r")
opcodes = list(map(int, f.readline().split(",")))
# evaluate opcodes in groups of 4
for i in range(0, len(opcodes), 4):
    if opcodes[i] == 99:  # halt
        break
    elif opcodes[i] == 1:  # add
        opcodes[opcodes[i+3]] = opcodes[opcodes[i+1]] + opcodes[opcodes[i+2]]
    elif opcodes[i] == 2:  # multiply
        opcodes[opcodes[i+3]] = opcodes[opcodes[i+1]] * opcodes[opcodes[i+2]]
    else:  # bad input
        print("error")
        break

print(opcodes[0])
