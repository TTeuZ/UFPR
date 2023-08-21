import os

for i in range(10):
    command = 'python3 ../src_files/knn.py ../results/representation.txt > ../results/knn_results/result' + \
        str(i+1) + '.txt'
    os.system(command)
