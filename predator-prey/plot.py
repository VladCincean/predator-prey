import matplotlib.pyplot as plt
import sys
import os

class Data:
    def __init__(self, N_predator, N_prey):
        self.N_predator = N_predator
        self.N_prey = N_prey

def extract_data_from_file(file):
    d = []
    with open(file, 'r') as f:
        for line in f.readlines():
            tokens = line.split()
            assert len(tokens) == 2

            data = Data(int(tokens[0]), int(tokens[1]))
            d.append(data)
    return d
    
def main():
    if len(sys.argv) != 2:
        print('usage: script.py <in_file>')
        exit(1)
    d = extract_data_from_file(sys.argv[1])
    x = [dd.N_prey for dd in d]
    y = [dd.N_predator for dd in d]
    plt.plot(x, y)
    plt.xlabel("N_Prey")
    plt.ylabel("N_Predator")
    plt.show()

if __name__ == '__main__':
    main()