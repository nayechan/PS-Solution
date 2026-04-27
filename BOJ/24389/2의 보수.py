x=int(input())
print(((x^-x)&2**32-1).bit_count())