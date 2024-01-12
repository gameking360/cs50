

def main():

    money = float(get_float()) * 100
    qtd_coins = 0

    while money >= 25:
        money -= 25
        qtd_coins += 1

    while money >= 10:
        money -=10
        qtd_coins += 1

    while money >= 5:
        money -= 5
        qtd_coins += 1

    while money != 0:
        money -= 1
        qtd_coins += 1


    print(qtd_coins)

def get_float():
    while True:
        try:
            x = input("Change owed: ")
            if float(x) > 0:
                break

        except:
            print("Não é float")
    return x

main()
