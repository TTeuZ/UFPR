import os

results_qtd = 20

for i in range(results_qtd):
    command = 'python3 ../src_files/knn.py ../results/representation.txt > ../results/knn_results/result' + \
        str(i+1) + '.txt'
    os.system(command)
