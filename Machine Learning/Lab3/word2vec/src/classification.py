from sklearn.datasets import load_svmlight_file
from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report

from sklearn import svm

# Reading the trainning and testing features
print("getting the data...")
x_train, y_train = load_svmlight_file(
    f"../imdb_master/features/train_500_10_2_1.txt")
x_test, y_test = load_svmlight_file(
    f"../imdb_master/features/test_500_10_2_1.txt")

# x_train, x_val, y_train, y_val = train_test_split(x, y, test_size=0.33, random_state=42)
print("fitting the model...")
model = svm.SVC(C=3, gamma=0.020756759688054908, kernel='rbf')
model.fit(x_train, y_train)

print("getting prediction...")
pred = model.predict(x_test)

print("showing results... \n")
cm = confusion_matrix(y_test, pred)
for i in range(2):
    for j in range(2):
        print(cm[i][j], end=' ')
    print('\n', end='')

print("\n\n")
print(classification_report(y_test, pred))
