from matplotlib import pyplot as plt
from pandas import Series
import numpy as np
import seaborn as sns
from mpl_toolkits.mplot3d import Axes3D
from sklearn.feature_extraction import DictVectorizer
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier


def distance(a, b):
    print("Equilid: ", np.linalg.norm(a - b))
    print("Square equilid: ", np.linalg.norm(a - b)**2)
    print("Чедышева: ", np.linalg.norm(a - b, ord=np.inf))
    print("Hamming distance: ", np.linalg.norm(a - b, ord=1))

# Задайте 4 точки в трехмерном пространстве, рассчитайте между ними расстояния
# по описанным в примере выше метрикам. Отобразите точки в трехмерном пространстве.
def task131():
    a = Series([1, 2, 4])
    b = Series([2, 12, 8])
    c = Series([21, 10, 7])
    d = Series([42, 9, 13])
    print("a -> b")
    distance(a, b)
    print("c -> d")
    distance(c, d)
    print("a -> c")
    distance(a, c)
    print("a -> d")
    distance(a, d)
    print("b -> c")
    distance(b, c)
    print("b -> d")
    distance(b, d)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(a[0], a[1], a[2])
    ax.scatter(b[0], b[1], b[2])
    ax.scatter(c[0], c[1], c[2])
    ax.scatter(d[0], d[1], d[2])
    plt.show()

# Создать 5x5 матрицу со значениями в строках от 0 до 4. Для создания необходимо использовать функцию arange.
def task132():
    array = np.array([np.arange(5) for _ in range(5)])
    print(array)

# Для предыдущего примера поэкспериментируйте с параметрами классификатора:
# Установите другое количество ближайших соседей (k = 1, 5, 10).
# Установите размер тестовой выборки 15% от всего датасета.
# Постройте графики и оцените качество моделей, проанализируйте результаты.
def task231():
    iris = sns.load_dataset("iris")
    X_train, X_test, y_train, y_test = train_test_split(
        iris.iloc[:, :-1],
        iris.iloc[:, -1],
        test_size=0.2,
    )

    k = 3

    X_train.head()
    y_train.head()

    model = KNeighborsClassifier(n_neighbors=k)
    model.fit(X_train, y_train)

    y_pred = model.predict(X_test)
    print(y_pred)

    plt.figure(figsize=(10, 7))
    sns.scatterplot(x = "petal_width", y = "petal_length", data=iris, hue = "species", s = 70)
    plt.xlabel("Ширина лепестка")
    plt.ylabel("Длина лепестка")
    plt.legend(loc=2)
    plt.grid()
    for i in range(len(y_test)):
        if np.array(y_test)[i] != y_pred[i]:
            plt.scatter(X_test.iloc[i, 3], X_test.iloc[i, 2], color="red", s=150)

    print(f"accuracy: {accuracy_score(y_test, y_pred):.3}")
    plt.show()

task231()

# Определите набор признаков человека, по аналогии из РТ 1, – например, цвет глаз и конвертируйте его в матрицу признаков.
def task332():
    eyeColors = ['red', 'green', 'blue', 'yellow', 'magenta', 'cyan', 'brown', 'purple', 'grey', 'silver', 'gold', 'red', 'blue']

    dataDict = [{color: 1} for color in eyeColors]

    dictvectorizer = DictVectorizer(sparse=False)

    feautres = dictvectorizer.fit_transform(dataDict)

    print("Исходный массив:")
    print(eyeColors)
    print("\nМатрица признаков:")
    print(feautres)
    print(f"\nНазвания признаков: {dictvectorizer.get_feature_names_out()}")

