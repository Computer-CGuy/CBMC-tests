import numpy as np

n = 96;k=5
collision_length = n//(k+1)
digest_size=(512//n)*n//8
indices_per_hash_output = 512//n
# hash_length = (k+1)*((collision_length+7)//8)
print(collision_length,digest_size)
X = []
for i in range(0, 2**(collision_length+1)):
    r = i % indices_per_hash_output
    if r == 0:
        # X_i = H(I||V||x_i)
        # curr_digest = digest.copy()
        # hash_xi(curr_digest, i/indices_per_hash_output)
        # tmp_hash = curr_digest.digest()
        tmp_hash = np.arange(60)
        # pass
    # print(tmp_hash)
    # print(r*n/8,(r+1)*n/8)
    X.append((
        (tmp_hash[r*n//8:(r+1)*n//8]),
        (i,)
    ))
print(X[0])
print(X[1])
print(X[2])
print(X[3])
print(X[4])
print(X[5])