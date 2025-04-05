from dataclasses import dataclass
import sys
sys.stdin = open('input.txt')
# sys.stdout = open('output.txt')

# ---------------------------------------------

import functools as f
import math as m
import re

@dataclass
class Order:
    before: int
    after: int


ii = lambda : int(input())
intList = lambda: [int(x) for x in input().split()]
istr = lambda : str(input())



orders: list[Order] = list()
update_list: list[list[int]] = list()
updates: list[dict] = list()

with open('input.txt') as f:
    for l in f:
        if '|' in l:
            x,y = l.split('|')
            orders.append(Order(int(x), int(y)))
        if ',' in l:
            update_list.append([int(x) for x in l.split(',')])
            updates.append({ int(x): idx for idx,x in enumerate(l.split(',')) })

def is_update_correct(update: dict, orders: list[Order]) -> bool:
    for order in orders:
        if order.before in update and order.after in update and update[order.before] > update[order.after]:
            return False
    return True

TOTAL = 0
for i, update in enumerate(updates):
    if is_update_correct(update, orders):
        print(update_list[i])
        TOTAL += update_list[i][len(update_list[i]) // 2]

print(f"TOTAL: {TOTAL}")  
