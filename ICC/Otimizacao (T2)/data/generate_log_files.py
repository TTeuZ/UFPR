import os

versions = ['v2']
matrix_sizes = [32, 33, 64, 65, 128, 129, 256, 257, 512, 1000, 2000, 4000, 6000, 10000]
groups = ['MEM', 'CACHE', 'FLOPS_DP']

# make
# os.system('../v1/ make')
# os.system('../v2/ make')

for v in versions:
    for m in matrix_sizes:
        for g in groups:
            # run tests for each group and each size of matrix for both versions
            command = 'likwid-perfctr -C 3 -g ' + g + ' -O -m ../' + v + '/invmat -r ' + str(m) + ' -i 10 > ./logs/' + v + '-' + str(m) + '-' + g + '.log'
            print('Gerando: ' + v + '-' + str(m) + '-' + g + '.log')
            os.system(command)