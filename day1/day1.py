f = open("day1.txt", "r")
inputs = map(int, f.readlines())
total = 0
for i in inputs:
    module_fuel = 0  # total fuel for the module
    added_fuel = (i // 3) - 2  # added fuel for each iteration of the fuel calculation
    while added_fuel > 0:
        module_fuel += added_fuel
        added_fuel = (added_fuel // 3) - 2
    total += module_fuel
print(total)
