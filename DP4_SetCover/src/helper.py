import operator
from functools import reduce

# return a list of sets composed from all possible combinations of subsets
def powerset(sets):
    n = len(sets)
    max_idx = 2**n-1
    op = operator.add
    powset = [frozenset(reduce(op, [sets[idx] for idx in set_indexes(n, i)])) for i in range(1, max_idx+1)]
    return powset

MAX_SIZE = 1000
fact_tab = [None for i in range(MAX_SIZE)]
fact_tab[0] = 1
fact_tab[1] = 1
def fast_factorial(x):
    if fact_tab[x] is None:
        fact_tab[x] = x * fast_factorial(x - 1)
    return fact_tab[x]

def nCk(n, k):
    return int(fast_factorial(n) / (fast_factorial(k) * fast_factorial(n - k)))

def get_size(n, i):
    for k in range(n+1):
        c = nCk(n, k)
        if c > i:
            return k, i
        else:
            i -= c

def set_indexes(n, i):
    s, i = get_size(n, i)
    result = []
    for k in range(s, 0, -1):
        prev_c = 0
        for v in range(k, n+1):
            c = nCk(v, k)
            if i < c:
                result.append(v-1)
                i -= prev_c
                break
            prev_c = c
    return result
