import csv
import sys
import re



def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    sequence = readFile(sys.argv[2])
    critters = readBigFile(sys.argv[1])
    critters.pop(0)
    dna = {}
    for c in critters:
        dna[c] = 0

    group = peoples(sys.argv[1])
    people = find(sequence,group,dna)

    if people != "0":
        print(people)
    else:
        print("No match.")


def readFile(file):
    with open(file,"r") as f:
        temp = f.read()
        return temp

def readBigFile(file):
    with open(file,"r") as f:
        reader = csv.reader(f)
        temp = {}
        for line in reader:
           temp = line
           break
        return temp


def peoples(file):
    with open(file,"r") as file:
        reader = csv.reader(file)
        next(reader)
        temp = {}
        for line in reader:
            temp[line[0]] = line[1:]

        return temp

def find(seq, people, check):
    for p in check:
        check[p] =  contSeq(seq,p)
    for k,v in people.items():
        if all(int(check[p]) == int(v[i]) for i,p in enumerate(check)):
            return k

    return "0"

def contSeq(seq,atual):
    qtd = 0
    maior = 0
    time = 0
    for c in range(len(seq)):
        if seq[c:c + len(atual)] == atual:
            qtd += 1
            time = len(atual)
            c += len(atual)
            if qtd > maior:
                maior = qtd

        elif time > 0:
            time -= 1

        elif time == 0:
            qtd = 0


    return maior

main()
