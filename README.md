# Tests

1) xor-array-cmbc.c SUCCESS
2) xor-array-32-length.c SUCCESS
3) xor-largers-array-cbmc.c SUCCESS
4) xor-2D-array.c SUCCESS
5) xor-array-bool.c SLOWER THAN xor-array-cmbc.c
6) xor-custom-array.c x_1||x_2||x_3||x_4||x_5 == 0; x_i=?


# ZCash Notes
1) n=200,k=9
2) How to digest? https://github.com/mjosaarinen/blake2_mjosref/blob/3491779dbf2465596b3db121701922cf7a9fd0a2/blake2b.c#L162  https://github.com/franziskuskiefer/Blake2b/blob/6d888db4f41523117e3a3cb110845bd0de392b74/src/blake2b_functions.c#L159
3) May be useful. https://github.com/buggywhip/blake2_py/blob/master/blake2.py

# SAT Solvers
SCryptoMiniSat http://amit.metodi.me/research/scrypto/

# Bisecting https://github.com/str4d/zcash-pow/blob/6ad7404b814e447048fd6713793eed8e0bbbd413/pow.py#L63
```py
for i in bar(range(0, 2**(collision_length+1))):
    r = i % indices_per_hash_output
    if r == 0:
        # X_i = H(I||V||x_i)
        curr_digest = digest.copy()
        hash_xi(curr_digest, i/indices_per_hash_output)
        tmp_hash = curr_digest.digest()
    X.append((
        expand_array(bytearray(tmp_hash[r*n/8:(r+1)*n/8]),
                     hash_length, collision_length),
        (i,)
    ))
```
For n = 200 and k=9,indices_per_hash_output=2
