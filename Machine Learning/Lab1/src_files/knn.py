#!/usr/bin/python
# -*- encoding: iso-8859-1 -*-

import sys
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn import preprocessing


def main(fname):
    # loads data
    data = np.loadtxt(fname)
    X_data = data[:, :-1]
    Y_data = data[:, -1]

    X_train, X_test, Y_train, y_test = train_test_split(
        X_data, Y_data, test_size=0.3)

    # cria um kNN
    neigh = KNeighborsClassifier(n_neighbors=3, metric='euclidean')
    neigh.fit(X_train, Y_train)
    y_pred = neigh.predict(X_test)

    # Resultados do fit
    # Accuracy
    print(neigh.score(X_test, y_test))

    # confusion matrix
    cm = confusion_matrix(y_test, y_pred)
    for i in range(10):
        for j in range(10):
            print(cm[i][j], end=' ')
        print('\n', end='')

    # classification report
    print(classification_report(y_test, y_pred))


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("Use: knn.py <file>")

    main(sys.argv[1])
