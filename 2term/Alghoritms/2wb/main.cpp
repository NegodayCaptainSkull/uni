#include <iostream>
#include <string>
using namespace std;

// task 1

struct Node1 {
    int data;
    Node1* next;
    Node1(int val = 0) : data(val), next(nullptr) {}
};

void printList1(Node1* head) {
    if (head == nullptr) {
        cout << "(пусто)";
    }
    while (head != nullptr) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

string checkList1(Node1 nodes[], int n) {
    for (int i = 0; i < n; i++) {
        Node1* expected = (i < n - 1) ? &nodes[i + 1] : nullptr;

        if (nodes[i].next == expected)
            continue;

        if (nodes[i].next == nullptr) {
            return "Ошибка: узел [" + to_string(i) + "] (data=" +
                   to_string(nodes[i].data) + ") — преждевременный NULL";
        }

        for (int j = 0; j < n; j++) {
            if (nodes[i].next == &nodes[j]) {
                if (j > i + 1)
                    return "Проскок: узел [" + to_string(i) + "] -> узел [" +
                           to_string(j) + "] (пропущено " +
                           to_string(j - i - 1) + " узлов)";
                else
                    return "Перескок: узел [" + to_string(i) + "] -> узел [" +
                           to_string(j) + "] (возврат назад/цикл)";
            }
        }

        return "Ошибка: узел [" + to_string(i) + "] указывает за пределы списка";
    }
    return "ok";
}

void task1() {
    Node1 nodes[5];
    for (int i = 0; i < 5; i++) nodes[i].data = (i + 1) * 10;
    nodes[0].next = &nodes[2];  // пропускает nodes[1]
    nodes[1].next = &nodes[2];
    nodes[2].next = &nodes[3];
    nodes[3].next = &nodes[4];
    nodes[4].next = nullptr;
    cout << "  Результат: " << checkList1(nodes, 5) << "\n\n";
}

// task 2

struct Node2 {
    int data;
    Node2* next;
    Node2(int val = 0) : data(val), next(nullptr) {}
};

void pushBack2(Node2*& head, Node2*& tail, Node2* node) {
    node->next = nullptr;
    if (head == nullptr) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

void freeList2(Node2* head) {
    while (head != nullptr) {
        Node2* temp = head;
        head = head->next;
        delete temp;
    }
}

void printList2(Node2* head) {
    if (head == nullptr) {
        cout << "(пусто)";
    }
    while (head != nullptr) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

void splitList2(Node2* head, int x, Node2*& lessList, Node2*& greaterEqList) {
    lessList = nullptr;
    greaterEqList = nullptr;

    Node2* lessTail = nullptr;
    Node2* greaterEqTail = nullptr;

    Node2* current = head;

    while (current != nullptr) {
        Node2* nextNode = current->next;

        if (current->data < x) {
            pushBack2(lessList, lessTail, current);
        } else {
            pushBack2(greaterEqList, greaterEqTail, current);
        }

        current = nextNode;
    }
}

void task2() {
    int n;
    cout << "Количество элементов: ";
    cin >> n;

    Node2* head = nullptr;
    Node2* tail = nullptr;

    cout << "Элементы списка: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        Node2* node = new Node2(val);
        pushBack2(head, tail, node);
    }

    int x;
    cout << "Пороговое значение X: ";
    cin >> x;

    cout << "\nИсходный список:   ";
    printList2(head);

    Node2* lessList = nullptr;
    Node2* greaterEqList = nullptr;
    splitList2(head, x, lessList, greaterEqList);

    cout << "\nСписок (< " << x << "):     ";
    printList2(lessList);

    cout << "Список (>= " << x << "):    ";
    printList2(greaterEqList);

    freeList2(lessList);
    freeList2(greaterEqList);
}

// task 3

struct Node3 {
    int value;
    Node3* next;
    Node3* prev;
    Node3(int val) : value(val), next(nullptr), prev(nullptr) {}
};

void pushBack3(Node3*& head, int val) {
    Node3* newNode = new Node3(val);

    if (head == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
    } else {
        Node3* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
}

void removeByValue3(Node3* head, int val) {
    if (head == nullptr) return;

    Node3* current = head;
    bool found = false;

    do {
        if (current->value == val) {
            found = true;
            break;
        }
        current = current->next;
    } while (current != head);

    if (!found) return;

    if (current->next == current) {
        delete current;
        head = nullptr;
        return;
    }

    Node3* prevNode = current->prev;
    Node3* nextNode = current->next;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    if (current == head) {
        head = nextNode;
    }

    delete current;
}

void printList3(Node3* head) {
    if (head == nullptr) {
        cout << "(пусто)" << endl;
        return;
    }

    Node3* current = head;
    do {
        cout << current->value;
        current = current->next;
        if (current != head) cout << " <-> ";
    } while (current != head);

    cout << " <-> (head)" << endl;
}

void task3() {
    Node3* head = nullptr;

    cout << "=== Добавление элементов ===" << endl;
    pushBack3(head, 10);
    pushBack3(head, 20);
    pushBack3(head, 30);
    pushBack3(head, 40);
    pushBack3(head, 50);

    printList3(head);

    cout << "\n=== Удаление 30 ===" << endl;
    removeByValue3(head, 30);

    printList3(head);
}

// task 4

struct Node4 {
    int value;
    Node4* next;
    Node4* prev;
    Node4(int val) : value(val), next(nullptr), prev(nullptr) {}
};

Node4* createList4(int n, int arr[]) {
    if (n == 0) return nullptr;
    Node4* head = new Node4(arr[0]);
    head->prev = nullptr;
    Node4* prev = head;
    for (int i = 1; i < n; i++) {
        Node4* newNode = new Node4(arr[i]);
        prev->next = newNode;
        newNode->prev = prev;
        prev = newNode;
    }
    prev->next = nullptr;
    return head;
}

void pushBack4(Node4* &head, int val) {
    Node4* newNode = new Node4(val);

    if (head == nullptr) {
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
    } else {
        Node4* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
        newNode->next = nullptr;
    }
}

void insertBeforeValue4(Node4* &head, int target, int val) {
    if (head == nullptr) return;

    Node4* current = head;
    while (current != nullptr && current->value != target) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Значение " << target << " не найдено" << endl;
        return;
    }

    Node4* newNode = new Node4(val);

    if (current == head) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else {
        Node4* prevNode = current->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = current;
        current->prev = newNode;
    }
}

void removeAll4(Node4*& head, int val) {
    Node4* current = head;

    while (current != nullptr) {
        if (current->value == val) {
            Node4* toDelete = current;
            Node4* prevNode = current->prev;
            Node4* nextNode = current->next;

            if (prevNode != nullptr) {
                prevNode->next = nextNode;
            } else {
                head = nextNode;
            }

            if (nextNode != nullptr) {
                nextNode->prev = prevNode;
            }

            current = nextNode;
            delete toDelete;
        } else {
            current = current->next;
        }
    }
}

int countNodes4(Node4* head) {
    int count = 0;
    Node4* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void printForwardList4(Node4* head) {
    Node4* current = head;
    while (current != nullptr) {
        cout << current->value << "<->";
        current = current->next;
    }
    cout << endl;
}

void printBackwardList4(Node4* head) {
    Node4* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    Node4* current = tail;

    while (current != nullptr) {
        cout << current->value << "<->";
        current = current->prev;
    }
    cout << endl;
}

bool isPalindrome4(Node4* head) {
    if (head == nullptr) return true;

    Node4* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    Node4* left = head;
    Node4* right = tail;

    while (left != right && left->prev != right) {
        if (left->value != right->value) {
            return false;
        }
        left = left->next;
        right = right->prev;
    }

    return true;
}

void task4() {
    int arr[5] = {5, 6, 1, 2, 12};
    Node4* list = createList4(5, arr);
    pushBack4(list, 6);
    insertBeforeValue4(list, 1, 3);
    insertBeforeValue4(list, 1, 3);
    cout << countNodes4(list) << endl;
    printForwardList4(list);
    removeAll4(list, 6);
    printBackwardList4(list);
    cout << isPalindrome4(list);
}

// task 5

struct Node5 {
    int digit;
    Node5* next;
    Node5(int val) : digit(val), next(nullptr) {}
};

void pushBack5(Node5*& head, Node5*& tail, int val) {
    Node5* newNode = new Node5(val);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void printList5(Node5* head) {
    while (head != nullptr) {
        cout << head->digit;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

void freeList5(Node5*& head) {
    while (head != nullptr) {
        Node5* temp = head;
        head = head->next;
        delete temp;
    }
}


Node5* createFromArray5(int arr[], int n) {
    Node5* head = nullptr;
    Node5* tail = nullptr;
    for (int i = 0; i < n; i++) {
        pushBack5(head, tail, arr[i]);
    }
    return head;
}

Node5* addReversed5(Node5* l1, Node5* l2) {
    Node5* resultHead = nullptr;
    Node5* resultTail = nullptr;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry != 0) {
        int sum = carry;

        if (l1 != nullptr) {
            sum += l1->digit;
            l1 = l1->next;
        }
        if (l2 != nullptr) {
            sum += l2->digit;
            l2 = l2->next;
        }

        carry = sum / 10;
        pushBack5(resultHead, resultTail, sum % 10);
    }

    return resultHead;
}

Node5* reverseList5(Node5* head) {
    Node5* prev = nullptr;
    Node5* current = head;

    while (current != nullptr) {
        Node5* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    return prev;
}

Node5* addForward5(Node5* l1, Node5* l2) {
    l1 = reverseList5(l1);
    l2 = reverseList5(l2);

    Node5* result = addReversed5(l1, l2);

    result = reverseList5(result);

    reverseList5(l1);
    reverseList5(l2);

    return result;
}

void task5() {
    cout << "=== Обратный порядок ===" << endl;
    int a1[] = {2, 4, 3};
    int b1[] = {5, 6, 4};

    Node5* l1 = createFromArray5(a1, 3);
    Node5* l2 = createFromArray5(b1, 3);

    cout << "  Число 1: "; printList5(l1);
    cout << "  Число 2: "; printList5(l2);

    Node5* sum1 = addReversed5(l1, l2);
    cout << "  Сумма:   "; printList5(sum1);
    cout << "  (342 + 465 = 807)" << endl;

    cout << "\n=== Прямой порядок (старшие разряды первые) ===" << endl;
    int a2[] = {3, 4, 2};
    int b2[] = {4, 6, 5};

    Node5* l5 = createFromArray5(a2, 3);
    Node5* l6 = createFromArray5(b2, 3);

    cout << "  Число 1: "; printList5(l5);
    cout << "  Число 2: "; printList5(l6);

    Node5* sum2 = addForward5(l5, l6);
    cout << "  Сумма:   "; printList5(sum2);
    cout << "  (342 + 465 = 807)" << endl;

    freeList5(l5);
    freeList5(l6);
    freeList5(l1);
    freeList5(l2);
    freeList5(sum1);
    freeList5(sum2);
}

// task 6

struct Node6 {
    int value;
    Node6* next;
    Node6(int val) : value(val), next(nullptr) {}
};

Node6* moveEvensToFront6(Node6* head) {
    if (head == nullptr) return nullptr;

    Node6 evenDummy(0), oddDummy(0);
    Node6* evenTail = &evenDummy;
    Node6* oddTail  = &oddDummy;

    Node6* current = head;

    while (current != nullptr) {
        if (current->value % 2 == 0) {
            evenTail->next = current;
            evenTail = current;
        } else {
            oddTail->next = current;
            oddTail = current;
        }
        current = current->next;
    }

    oddTail->next = nullptr;

    evenTail->next = oddDummy.next;

    return evenDummy.next != nullptr ? evenDummy.next : oddDummy.next;
}

void pushBack6(Node6*& head, Node6*& tail, int val) {
    Node6* newNode = new Node6(val);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void printList6(Node6* head) {
    if (head == nullptr) {
        cout << "(пусто)" << endl;
        return;
    }
    while (head != nullptr) {
        cout << head->value;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

void freeList6(Node6*& head) {
    while (head != nullptr) {
        Node6* temp = head;
        head = head->next;
        delete temp;
    }
}

void task6() {
    Node6* head = nullptr; Node6* tail = nullptr;
    for (int v : {5, 2, 8, 3, 1, 6}) pushBack6(head, tail, v);
    cout << "Вход:  "; printList6(head);
    head = moveEvensToFront6(head);
    cout << "Выход: "; printList6(head);
    freeList6(head);

}

// task 7

struct Node7 {
    int value;
    Node7* next;
    Node7* prev;
    Node7(int val) : value(val), next(nullptr), prev(nullptr) {}
};


void pushBack7(Node7*& head, Node7*& tail, int val) {
    Node7* newNode = new Node7(val);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void printList7(Node7* head) {
    if (head == nullptr) {
        cout << "(пусто)" << endl;
        return;
    }
    while (head != nullptr) {
        cout << head->value;
        if (head->next) cout << " - ";
        head = head->next;
    }
    cout << endl;
}

void freeList7(Node7*& head) {
    while (head != nullptr) {
        Node7* temp = head;
        head = head->next;
        delete temp;
    }
}


Node7* intersect7(Node7* l1, Node7* l2) {
    Node7* resultHead = nullptr;
    Node7* resultTail = nullptr;

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->value < l2->value) {
            l1 = l1->next;
        } else if (l1->value > l2->value) {
            l2 = l2->next;
        } else {
            pushBack7(resultHead, resultTail, l1->value);
            l1 = l1->next;
            l2 = l2->next;
        }
    }

    return resultHead;
}

void task7() {
    Node7* l1h = nullptr; Node7* l1t = nullptr;
    for (int v : {2, 2, 3, 5, 7, 7, 9}) pushBack7(l1h, l1t, v);

    Node7* l2h = nullptr; Node7* l2t = nullptr;
    for (int v : {2, 2, 2, 3, 3, 7, 8}) pushBack7(l2h, l2t, v);

    cout << "L1:     "; printList7(l1h);
    cout << "L2:     "; printList7(l2h);

    Node7* result = intersect7(l1h, l2h);
    cout << "Выход:  "; printList7(result);

    freeList7(l1h); freeList7(l2h); freeList7(result);
}

int main() {
    task7();
}