f = open("day5.txt", "r")
opcodes = list(map(int, f.readline().split(",")))

# evaluate opcodes in groups
i = 0
while i < len(opcodes):

    # get inputs
    command = opcodes[i]
    parameters = list()
    if (command % 100) == 1 or (command % 100) == 2 or (command % 100 == 7) or (command % 100 == 8):  # get 3 parameters
        for p in range(1, 3):
            if (command // 10**(p+1)) % 10 == 0:  # position mode
                parameters.append(opcodes[opcodes[i+p]])
            else:  # immediate mode
                parameters.append(opcodes[i+p])
        parameters.append(opcodes[i+3])

    elif (command % 100) == 5 or (command % 100) == 6:  # get 2 parameters
        for p in range(1, 3):
            if (command // 10**(p+1)) % 10 == 0:  # position mode
                parameters.append(opcodes[opcodes[i+p]])
            else:  # immediate mode
                parameters.append(opcodes[i+p])

    elif (command % 100) == 3 or (command % 100) == 4:  # get 1 parameter, always in position mode
        parameters.append(opcodes[i+1])

    # evaluate operation
    command = command % 100
    if command == 99:  # halt
        break

    elif command == 1:  # add
        opcodes[parameters[2]] = parameters[0] + parameters[1]
        i += 4

    elif command == 2:  # multiply
        opcodes[parameters[2]] = parameters[0] * parameters[1]
        i += 4

    elif command == 3:  # set
        opcodes[parameters[0]] = int(input("Enter an integer: "))
        i += 2
    elif command == 4:  # get
        print(opcodes[parameters[0]])
        i += 2

    elif command == 5:  # jump if true
        if parameters[0] != 0:
            i = parameters[1]
        else:
            i += 3

    elif command == 6:  # jump if false
        if parameters[0] == 0:
            i = parameters[1]
        else:
            i += 3

    elif command == 7:  # less than
        if parameters[0] < parameters[1]:
            opcodes[parameters[2]] = 1
        else:
            opcodes[parameters[2]] = 0
        i += 4

    elif command == 8:  # equals
        if parameters[0] == parameters[1]:
            opcodes[parameters[2]] = 1
        else:
            opcodes[parameters[2]] = 0
        i += 4

    else:  # bad input
        print("error")
        break
