
final = [".","!","?"]


def main():

    text = input("Text: ")
    char = 0
    words = 0
    phrase = 0


    for i in range(len(text)):
        c = text[i]
        if c in final:
            phrase += 1
            words += 1

        elif (c == " " or c == ",") and (text[i -1] not in final and text[i - 1] != ","):
            words += 1

        elif c.isalpha():
            char += 1

    averageChar = (char / words) * 100
    averagePhrase = (phrase / words) * 100

    indice = 0.0588 * averageChar  - 0.296 * averagePhrase - 15.8


    if indice >= 16:
        print("Grade 16+")
    elif indice < 1:
        print("Before Grade 1")
    else:
        print(f"Grade: {round(indice)}")


main()

