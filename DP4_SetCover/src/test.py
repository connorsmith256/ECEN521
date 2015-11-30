#!/usr/local/bin/python3

import sys

from helper import *

DEBUG = False

def print_label(label):
    print('----------------------\n{}\n----------------------'.format(label))

# read input
filename = sys.argv[1]
input_lines = [line.rstrip() for line in open(filename) if line.strip() != '']

max_n = int(input_lines[0])
num_lines = int(input_lines[1])
print_label('Maximum number, Number of sets:')
print(max_n, num_lines)

sets = [[int(x) for x in line.split(' ')] for line in input_lines[2:]]
print_label('Input sets:')
for i, s in enumerate(sets):
    print('{:3d}'.format(i+1), s)

# generate all possible subsets
powset = powerset(sets)

if DEBUG:
    print_label('Possible subsets ({0}):'.format(len(powset)))
    for i, subset in enumerate(powset):
        print(i+1, set_indexes(num_lines, i+1), subset)

print_label('Subset Covers:')
for i, subset in enumerate(powset):
    if len(subset) == max_n:
        indexes = sorted(list(map(lambda x: x+1, set_indexes(num_lines, i+1))))
        print(len(indexes))
        for i in indexes:
            print('({})'.format(i), ' '.join(str(val) for val in sets[i-1]))
        break