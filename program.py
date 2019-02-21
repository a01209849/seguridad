def permutate(l, perm):
    aux = list(l)
    n = len(l)
    for i in range(n):
        l[i] = aux[perm[i]]


def sub_keys(key):
    bits = [int(i) for i in key]
    perm = [2,4,1,6,3,9,0,8,7,5]
    permutate(bits, perm)
    b1 = bits[:5]
    b2 = bits[5:]
    permutate(b1, [1,2,3,4,0])
    permutate(b2, [1,2,3,4,0])
    joined = b1+b2
    permutate(joined, [5,2,6,3,7,4,9,8,0,1])
    k1 = joined[:8]
    permutate(b1, [2,3,4,0,1])
    permutate(b2, [2,3,4,0,1])
    joined = b1+b2
    permutate(joined, [5,2,6,3,7,4,9,8,0,1])
    k2 = joined[:8]
    return [k1, k2]


def booleanList_to_decimal(l):
    num_s = ''.join(str(e) for e in l)
    return int(num_s, 2)


def s_box(s, h):
    res = list()
    tmp = str(h[0]) + str(h[1])
    i = int(str(h[0]) + str(h[3]), 2)
    j = int(str(h[1]) + str(h[2]), 2)
    num = bin(s[i][j])[2:]
    if len(num) == 2:
        for e in map(int, num):
            res.append(e)
    else:
        res = [0] + [int(num)]
    return res


def feistel(key, b):
    left = b[:4]
    right = b[4:]
    expansion = [right[3],right[0],right[1],right[2],right[1],right[2],right[3],right[0]]
    key_num = booleanList_to_decimal(key)
    exp_int = booleanList_to_decimal(expansion)
    xor = bin(key_num ^ exp_int)[2:]
    n = len(xor)
    key_exp = [0 for i in range(8 - n)]
    for e in map(int, xor):
        key_exp.append(e)
    h1 = key_exp[:4]
    h2 = key_exp[4:]
    s0 = [[1,0,3,2], [3,2,1,0], [0,2,1,3], [3,1,3,2]]
    s1 = [[0,1,2,3], [2,0,1,3], [3,0,1,0], [2,1,0,3]]
    s_res = s_box(s0,h1) + s_box(s1,h2)
    permutate(s_res, [1,3,2,0])
    s_res_num = booleanList_to_decimal(s_res)
    left_num = booleanList_to_decimal(left)
    xor = bin(s_res_num ^ left_num)[2:]
    n = len(xor)
    res = [0 for i in range(4 - n)]
    for e in map(int, xor):
        res.append(e)
    return res + right


def encrypt(key, text, flag):
    text = [int(i) for i in text]
    #INITIAL PERMUTATION
    permutate(text, [1,5,2,0,3,7,4,6])
    #GENERATE SUBKEYS
    if flag:
        k1,k2 = sub_keys(key)
    else:
        k1,k2 = sub_keys(key)
    #FEISTEL STEP
    fir_round = feistel(k1, text)
    inv = fir_round[4:] + fir_round[:4]
    final = feistel(k2, inv)
    permutate(final, [3,0,2,4,6,1,7,5])
    return final


def main():
    operation = input()
    key = input()
    text = input()
    if operation == 'E':
        final = encrypt(key, text, 1)
    else:
        final = encrypt(key, text, 0)
    res = ''
    for e in map(str, final):
        res += e
    print(res)


main()