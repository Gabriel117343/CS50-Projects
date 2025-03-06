import cs50

coins = [25, 10, 5, 1]

while True:

    try:
        user_cash = cs50.get_float("Change owed: ")
        if (user_cash > 0):
            break
    except ValueError:
        continue

# Conver dolars to cents, ensuring avoid problems with floats
cents = round(user_cash * 100)

# counter of coins
coin_count = 0
# calculate the min coins number
for coin in coins:
   coin_count += cents // coin # make integer division (round to below)
   cents %= coin # update with the rest of division
print(coin_count)
