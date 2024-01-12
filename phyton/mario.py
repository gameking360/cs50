


def main():
    altura = get_int_positive()

    for i in range(altura):
        if altura != 1:
            print(" " * (altura - i - 1), end = "")

        print("#" * (i + 1), end = "  ")
        print("#" * (i + 1))




def get_int_positive():
    while True:
        heigth = input("Height: ")
        if heigth.isdigit() and int(heigth) > 0 and int(heigth) < 9 :
            break

    return int(heigth)


main()

