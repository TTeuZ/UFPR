import linecache
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from statistics import mean, mode, stdev, variance

results_qtd = 10

#  Accuracy variables
accuracy_list = []
df_accuracy = pd.DataFrame(columns=['index', 'result_file', 'accuracy'])

# confusion matrix variables
confusion_matrices = []
confusion_matrix_avg = None

# f-score variables
f_score_matrices = []
f_score_matrix_avg = None

for index in range(results_qtd):
    file = '../results/knn_results/result' + str(index + 1) + '.txt'

    # Accuracy
    data = linecache.getline(file, 1)
    value = float(data[:-1])

    accuracy_list.append(value)
    new_row = [(index + 1), f'result {index + 1}', value]
    df_accuracy = pd.concat([df_accuracy, pd.DataFrame(
        [new_row], columns=df_accuracy.columns)], ignore_index=True)

    # Confusion matrix
    confusion_matrix = []
    for row in range(2, 12):
        data = linecache.getline(file, row)
        confusion_matrix.append([int(x) for x in data.split(' ')[:-1]])

    temp_matrix = np.matrix(confusion_matrix)
    confusion_matrices.append(temp_matrix)
    if index != 0:
        confusion_matrix_avg = confusion_matrix_avg.__add__(temp_matrix)
    else:
        confusion_matrix_avg = temp_matrix

    # f-score
    f_score = []
    for row in range(14, 24):
        data = linecache.getline(file, row)
        f_score.append([float(x) for x in data.split(' ') if x != ''][1:-1])

    temp_matrix = np.matrix(f_score)
    f_score_matrices.append(temp_matrix)
    if index != 0:
        f_score_matrix_avg = f_score_matrix_avg.__add__(temp_matrix)
    else:
        f_score_matrix_avg = temp_matrix

#  Accuracy chart (svg file)
plt.figure(figsize=(7, 4.5))
ax = df_accuracy.set_index('index').plot(marker='o', color=['darkorange'])
ax.set_ylabel('Acurracy')
ax.set_xlabel('Attempt')
ax.set_title('Model accuracy')
plt.grid()
plt.savefig('../results/final/accuracy.svg', bbox_inches='tight')

# Creating final file (txt file)
file = open('../results/final/final.txt', 'w')

# Accuracy results
file.write(f"max: {max(accuracy_list)}\n")
file.write(f"media: {mean(accuracy_list)}\n")
file.write(f"moda: {mode(accuracy_list)}\n")
file.write(f"desvio padrao: {stdev(accuracy_list)}\n")
file.write(f"variancia: {variance(accuracy_list)}\n")

# Confusion matrix results
file.write("\nAvarage of confusion matrix:\n")
confusion_matrix_avg = confusion_matrix_avg.__truediv__(results_qtd)
for row in confusion_matrix_avg:
    file.write(f"{str(row)[2:-2]}\n")

file.write("\nBest of confusion matrix:\n")
best_matrix = confusion_matrices[accuracy_list.index(max(accuracy_list))]
for row in best_matrix:
    file.write(f"{str(row)[2:-2]}\n")

# f-score results
file.write("\nAvarage of f-score:\n")
f_score_matrix_avg = f_score_matrix_avg.__truediv__(results_qtd)
for index, row in enumerate(f_score_matrix_avg):
    file.write(f"{index} {str(row)[2:-2]}\n")

file.write("\nBest of f-score:\n")
best_matrix = f_score_matrices[accuracy_list.index(max(accuracy_list))]
for index, row in enumerate(best_matrix):
    file.write(f"{index} {str(row)[2:-2]}\n")
