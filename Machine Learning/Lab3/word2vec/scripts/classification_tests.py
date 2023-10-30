from sklearn.datasets import load_svmlight_file
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report

from sklearn import svm

import config

# Reading the trainning and testing features
x_train, y_train = load_svmlight_file(f"../features/train_{config.VectorSize}_{config.WindowSize}_{config.MinCount}.txt")
x_test, y_test = load_svmlight_file(f"../features/test_{config.VectorSize}_{config.WindowSize}_{config.MinCount}.txt")

# x_train, x_val, y_train, y_val = train_test_split(x, y, test_size=0.33, random_state=42)

model = svm.SVC(C=24, gamma=0.005009627595770921, kernel='rbf')
model.fit(x_train, y_train)

pred = model.predict(x_test)

cm = confusion_matrix(y_test, pred)
for i in range(2):
    for j in range(2):
        print(cm[i][j], end=' ')
    print('\n', end='')

print("\n\n")
print(classification_report(y_test, pred))