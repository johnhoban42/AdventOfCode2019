# password range: 123257 - 647015
lo = 123257
hi = 647015
total = 0

# For each iteration, "build" the number so that the digits are increasing.
# In this case, all numbers in the range above hi // 10^6 don't have increasing digits
for d1 in range(lo // 10**5, hi // 10**5):
    for d2 in range(d1, 10):
        for d3 in range(d2, 10):
            for d4 in range(d3, 10):
                for d5 in range(d4, 10):
                    for d6 in range(d5, 10):
                        if 100000 * d1 + 10000 * d2 + 1000 * d3 + 100 * d4 + 10 * d5 + d6 < lo:
                            continue
                        # Check for doubled digits while also checking the "boundaries" of these doubles
                        # Only count doubles that aren't inside larger strings of the same digits
                        if (d1 == d2 and d2 != d3) or (d1 != d2 and d2 == d3 and d3 != d4) or \
                            (d2 != d3 and d3 == d4 and d4 != d5) or (d3 != d4 and d4 == d5 and d5 != d6) \
                            or (d4 != d5 and d5 == d6):
                            total += 1

print(total)
