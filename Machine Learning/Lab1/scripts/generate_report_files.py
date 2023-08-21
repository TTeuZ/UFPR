import os
import linecache
import pandas as pd
import matplotlib.pyplot as plt

accuracy_list = []
df_accuracy = pd.DataFrame(columns=['index', 'result_file', 'accuracy'])

for i in range(10):
    file = '../results/knn_results/result' + str(i+1) + '.txt'

    # Accuracy
    data = linecache.getline(file, 1)
    value = float(data[:-1])

    accuracy_list.append(value)
    new_row = [(i + 1), f'result {i+1}', value]
    df_accuracy = pd.concat([df_accuracy, pd.DataFrame(
        [new_row], columns=df_accuracy.columns)], ignore_index=True)


#  Accuracy


plt.figure(figsize=(7, 4.5))
ax = df_accuracy.set_index('index').plot(
    marker='o', color=['darkorange'])
ax.set_ylabel('Acurracy')
ax.set_xlabel('Attempt')
ax.set_title('Model accuracy')
plt.grid()
plt.savefig('../results/accuracy/accuracy.svg', bbox_inches='tight')
