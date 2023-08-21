import linecache
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from statistics import mean, mode, stdev, variance

results_qtd = 20

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

    temp_matrix = np.array(confusion_matrix)
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

    temp_matrix = np.array(f_score)
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
file.write(f"max: {max(accuracy_list):.5f}\n")
file.write(f"media: {mean(accuracy_list):.5f}\n")
file.write(f"moda: {mode(accuracy_list):.5f}\n")
file.write(f"desvio padrao: {stdev(accuracy_list):.5f}\n")
file.write(f"variancia: {variance(accuracy_list):.5f}\n")

# Confusion matrix results
file.write("\nAvarage of confusion matrix:\n")
confusion_matrix_avg = confusion_matrix_avg.__truediv__(results_qtd)
for i in range(10):
    for j in range(10):
        file.write(f"{confusion_matrix_avg[i][j]:.3f}\t\t")
    file.write('\n')

file.write("\nBest of confusion matrix:\n")
best_matrix = confusion_matrices[accuracy_list.index(max(accuracy_list))]
for i in range(10):
    for j in range(10):
        file.write(f"{best_matrix[i][j]} ")
    file.write('\n')

# f-score results
file.write("\nAvarage of f-score:\n")
file.write("\t\tprecision\trecall\t\tf1-score\n")
f_score_matrix_avg = f_score_matrix_avg.__truediv__(results_qtd)
for i in range(10):
    file.write(f"{i}\t\t")
    for j in range(3):
        file.write(f"{f_score_matrix_avg[i][j]:.3f}\t\t\t")
    file.write('\n')

file.write("\nBest of f-score:\n")
file.write("\t\tprecision\trecall\t\tf1-score\n")
best_matrix = f_score_matrices[accuracy_list.index(max(accuracy_list))]
for i in range(10):
    file.write(f"{i}\t\t")
    for j in range(3):
        file.write(f"{best_matrix[i][j]:.3f}\t\t\t")
    file.write('\n')
