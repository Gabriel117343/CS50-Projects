while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height <= 8:
            break
    except ValueError:
        continue

for i in range(height):
    print(' ' * (height - i - 1) + '#' * (i + 1))
