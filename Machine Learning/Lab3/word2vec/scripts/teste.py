import keras
from sklearn.datasets import load_svmlight_file
from sklearn.model_selection import train_test_split

import config

# Reading the trainning and testing features
x, y = load_svmlight_file(f"../features/train_{config.VectorSize}_{config.WindowSize}_{config.MinCount}.txt")
x_test, y_test = load_svmlight_file(f"../features/test_{config.VectorSize}_{config.WindowSize}_{config.MinCount}.txt")

x_train, x_val, y_train, y_val = train_test_split(x, y, test_size=0.33, random_state=42)

# Saving for the confusion matrix
label = y_test

# converts the labels to a categorical one-hot-vector
y_train = keras.utils.to_categorical(y_train, num_classes=2)
y_val = keras.utils.to_categorical(y_val, num_classes=2)
y_test = keras.utils.to_categorical(y_test, num_classes=2)

print(y_val)