

def main():

    numCard = input("Number: ")

    t = Validator(numCard)

    if t:
        CardCompany(numCard)

    else:
        print("INVALID")




def validCarton(number):
    total = 0
    time = True

    for i in range(len(number)-1,-1,-1):

        if not time:
            time = True
            digit = int(number[i]) * 2
            if digit >= 10:
                total += int(digit/10)
                total += int(digit%10)
            else:
                total += digit
        elif time:
            time = False
            total += int(number[i])

    return total


def Validator(number):

    resultado = validCarton(number)
    if resultado%10 == 0 and len(number) >= 13 and len(number) <= 16:
        return True
    return False

def CardCompany(number):
    if int(number[0]) == 4:
        print("VISA")

    elif int(number[0]) == 3 and (int(number[1]) == 4 or int(number[1]) == 7):
        print("AMEX")

    elif int(number[0]) == 5 and (int(number[1]) >= 1 and int(number[1]) <= 5):
        print("MASTERCARD")

main()
