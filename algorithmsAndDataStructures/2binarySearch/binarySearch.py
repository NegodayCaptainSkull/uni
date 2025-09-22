print("") #Это чисто для меня, потому что у меня странные выводы в vscode
nums = [1, 2, 3, 5, 6, 8, 9]

def insertElement(arr, index, key): #Собственноручная реализация вставки элемента в определенный индекс массива (arr.insert())
  newArr = arr[:index]
  newArr.append(key)
  newArr += arr[index:len(arr)]
  return newArr

def binarySearch(arr, key):
  first = 0
  last = len(arr) - 1

  if len(arr) == 0: #Проверяем если вдруг был передан пустой массив
        arr.append(key)
        return 0
  
  if (key > arr[last]): #Если ключ больше максимального элемента массива вставляем в конец
    arr = insertElement(arr, last+1, key)
    return last + 1
  elif (key < arr[0]): #Если ключ меньше минимального элемента массива вставляем в начало
    arr = insertElement(arr, 0, key)
    return 0

  while first <= last:
    mid = (last + first) // 2
    midVal = arr[mid]
    if (arr[mid] < key and arr[mid + 1] > key): # Проверяем если ключ по значению между двумя соседними элементами
      arr = insertElement(arr, mid+1, key)
      return mid + 1
    elif (arr[mid] > key and arr[mid - 1] < key):
      arr = insertElement(arr, mid, key)
      return mid
    if midVal == key:
      return mid
    if midVal > key:
      last = mid - 1
    if midVal < key:
      first = mid + 1
  
  return -1

# print(binarySearch(nums, 7))


def mountain (arr):
  if len(arr) < 3: #Первое условие задачи
    return -1
  
  first = 0
  last = len(arr) - 1

  top = -1

  while first <= last:
    mid = (first + last) // 2
    midVal = arr[mid]
    if (midVal > arr[mid-1] and mid == len(arr)-1) or (midVal > arr[mid-1] and midVal > arr[mid+1]): #Первая часть выражения проверяет если массив был отсортирован по возрастанию и бинарный поиск дошел до последнего элемента. 
      # Вторая часть для неотсортированного массива проверяет если значение больше правого и левого элементов - значит нашли вероятную вершину. Если массив отсортирован по убыванию то это тоже работает вторая часть условного выражения,
      # т.к. arr[0] > arr[1] и arr[0] > arr[-1]
      top = mid #Записываем индекс вершины
      break
    if midVal < arr[mid-1]: #Если соседний элемент больше, значит это точно не вершина, меняем область поиска.
      last = mid - 1
    if midVal < arr[mid+1]:
      first = mid + 1

  for i in range(top): #Проверяем наличие других вершин. По условию задачи вершина может быть только одна, если вершины две, то не выполняется второе условие.
    if arr[i] > arr[i+1]:
      return -1
  for i in range(top+1, len(arr) - 1):
    if arr[i] < arr[i+1]:
      return -1
  
  return top

# print(mountain([2, 3, 5, 6, 7, 8, 9, 19, 10, 5, 2, 1]))


def negativeAndPositiveNums(arr):
  index = binarySearch(arr, 0) # Используем двоичный поиск, реализованный в первом задании, для индекса, на котором мог бы стоять ноль. Это будет разделителем отрицательных и положительных чисел.
  if (index > len(arr) - index): #Количество отрицательных чисел равно индексу 0, а положительные это все минус отрицательные
    return index
  elif (index < len(arr) - index):
    return len(arr) - index
  return index

# print(negativeAndPositiveNums([-12, -11, -8, -7, -5, -3, -3, -1, 1, 1, 4, 6, 8, 9, 9, 10, 11]))

def findCounts(arr):
  counts = []
  for i in range(len(arr)):
    newArr = sorted(arr[i+1:])
    index = binarySearch(newArr, arr[i]) #Из первого задания. Смотрим, на каком месте стояло бы число в срезе.
    counts.append(index) #Все числа идущие раньше этого числа будут меньше. Их количество равно индексу.
  return counts

print(findCounts([5, 2, 6, 1, 5, 2, 1, 3, 0]))