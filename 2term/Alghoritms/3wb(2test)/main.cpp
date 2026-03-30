#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>

using namespace std;

// ============================================================================
//                  ОБЩИЕ СТРУКТУРЫ И ФУНКЦИИ ДЛЯ BST (Задания 1, 2)
// ============================================================================

struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

BSTNode* bstInsert(BSTNode* root, int val) {
    if (!root) return new BSTNode(val);
    if (val < root->value)
        root->left = bstInsert(root->left, val);
    else
        root->right = bstInsert(root->right, val);
    return root;
}

void bstPreorder(BSTNode* root) {
    if (!root) return;
    cout << root->value << " ";
    bstPreorder(root->left);
    bstPreorder(root->right);
}

void bstInorder(BSTNode* root) {
    if (!root) return;
    bstInorder(root->left);
    cout << root->value << " ";
    bstInorder(root->right);
}

void bstPostorder(BSTNode* root) {
    if (!root) return;
    bstPostorder(root->left);
    bstPostorder(root->right);
    cout << root->value << " ";
}

int bstHeight(BSTNode* root) {
    if (!root) return 0;
    return 1 + max(bstHeight(root->left), bstHeight(root->right));
}

BSTNode* bstSearch(BSTNode* root, int val) {
    if (!root || root->value == val) return root;
    if (val < root->value) return bstSearch(root->left, val);
    return bstSearch(root->right, val);
}

BSTNode* bstFindMin(BSTNode* root) {
    while (root && root->left) root = root->left;
    return root;
}

BSTNode* bstDelete(BSTNode* root, int val) {
    if (!root) return nullptr;
    if (val < root->value)
        root->left = bstDelete(root->left, val);
    else if (val > root->value)
        root->right = bstDelete(root->right, val);
    else {
        if (!root->left) {
            BSTNode* tmp = root->right;
            delete root;
            return tmp;
        }
        if (!root->right) {
            BSTNode* tmp = root->left;
            delete root;
            return tmp;
        }
        BSTNode* succ = bstFindMin(root->right);
        root->value = succ->value;
        root->right = bstDelete(root->right, succ->value);
    }
    return root;
}

void bstFree(BSTNode* root) {
    if (!root) return;
    bstFree(root->left);
    bstFree(root->right);
    delete root;
}

// ============================================================================
//                          ЗАДАНИЕ 1 — BST с операциями
// ============================================================================

void task1() {
    cout << "\n========== ЗАДАНИЕ 1: Двоичное дерево поиска ==========\n";
    int n;
    cout << "Введите количество элементов дерева: ";
    cin >> n;

    BSTNode* root = nullptr;
    cout << "Сгенерированные значения: ";
    for (int i = 0; i < n; i++) {
        int val = rand() % 100 + 1;
        cout << val << " ";
        root = bstInsert(root, val);
    }
    cout << endl;

    // а) добавление
    cout << "\nа) Добавление нового узла. Введите значение: ";
    int v; cin >> v;
    root = bstInsert(root, v);
    cout << "Узел " << v << " добавлен.\n";

    // б) обходы
    cout << "\nб) Обходы дерева:\n";
    cout << "  Прямой (preorder):       "; bstPreorder(root);  cout << endl;
    cout << "  Симметричный (inorder):  "; bstInorder(root);   cout << endl;
    cout << "  Обратный (postorder):    "; bstPostorder(root); cout << endl;

    // в) высота
    cout << "\nв) Глубина (высота) дерева: " << bstHeight(root) << endl;

    // г) поиск
    cout << "\nг) Поиск элемента. Введите значение: ";
    int s; cin >> s;
    cout << (bstSearch(root, s) ? "Найден.\n" : "Не найден.\n");

    // д) удаление
    cout << "\nд) Удаление узла. Введите значение: ";
    int d; cin >> d;
    root = bstDelete(root, d);
    cout << "Дерево после удаления (inorder): ";
    bstInorder(root);
    cout << endl;

    bstFree(root);
}

// ============================================================================
//                    ЗАДАНИЕ 2 — Ближайший балл в BST
// ============================================================================

void task2() {
    cout << "\n========== ЗАДАНИЕ 2: Ближайший балл ==========\n";
    int n;
    cout << "Введите количество баллов: ";
    cin >> n;

    BSTNode* root = nullptr;
    cout << "Введите баллы: ";
    for (int i = 0; i < n; i++) {
        int val; cin >> val;
        root = bstInsert(root, val);
    }

    int x;
    cout << "Введите новый результат x: ";
    cin >> x;

    int closest = -1, minDiff = INT_MAX;
    BSTNode* cur = root;
    while (cur) {
        int diff = abs(cur->value - x);
        if (diff < minDiff || (diff == minDiff && cur->value < closest)) {
            minDiff = diff;
            closest = cur->value;
        }
        if (x < cur->value)      cur = cur->left;
        else if (x > cur->value) cur = cur->right;
        else                     break;          // точное совпадение
    }

    cout << "Ближайший балл: " << closest << endl;
    bstFree(root);
}

// ============================================================================
//                     ЗАДАНИЕ 3 — Телефонная книга (BST)
// ============================================================================

struct PhoneNode {
    string name;
    vector<string> phones;
    PhoneNode *left, *right;
    PhoneNode(const string& n, const string& p)
        : name(n), left(nullptr), right(nullptr) { phones.push_back(p); }
};

PhoneNode* phoneInsert(PhoneNode* root, const string& name, const string& phone) {
    if (!root) return new PhoneNode(name, phone);
    if (name < root->name)      root->left  = phoneInsert(root->left,  name, phone);
    else if (name > root->name) root->right = phoneInsert(root->right, name, phone);
    else                        root->phones.push_back(phone);   // тот же человек
    return root;
}

PhoneNode* phoneSearch(PhoneNode* root, const string& name) {
    if (!root || root->name == name) return root;
    return (name < root->name) ? phoneSearch(root->left, name)
                               : phoneSearch(root->right, name);
}

PhoneNode* phoneFindMin(PhoneNode* r) {
    while (r && r->left) r = r->left;
    return r;
}

PhoneNode* phoneDelete(PhoneNode* root, const string& name) {
    if (!root) return nullptr;
    if (name < root->name)      root->left  = phoneDelete(root->left,  name);
    else if (name > root->name) root->right = phoneDelete(root->right, name);
    else {
        if (!root->left)  { PhoneNode* t = root->right; delete root; return t; }
        if (!root->right) { PhoneNode* t = root->left;  delete root; return t; }
        PhoneNode* s = phoneFindMin(root->right);
        root->name = s->name;
        root->phones = s->phones;
        root->right = phoneDelete(root->right, s->name);
    }
    return root;
}

void phoneInorder(PhoneNode* root) {
    if (!root) return;
    phoneInorder(root->left);
    cout << "  " << root->name << ": ";
    for (size_t i = 0; i < root->phones.size(); i++)
        cout << (i ? ", " : "") << root->phones[i];
    cout << endl;
    phoneInorder(root->right);
}

void phoneFree(PhoneNode* root) {
    if (!root) return;
    phoneFree(root->left);
    phoneFree(root->right);
    delete root;
}

void task3() {
    cout << "\n========== ЗАДАНИЕ 3: Телефонная книга ==========\n";
    PhoneNode* root = nullptr;

    while (true) {
        cout << "\n1-Добавить  2-Найти  3-Удалить  4-Все записи  0-Назад\nВыбор: ";
        int ch; cin >> ch;
        if (ch == 0) break;

        string name, phone;
        switch (ch) {
        case 1:
            cout << "Имя: ";    cin >> name;
            cout << "Телефон: "; cin >> phone;
            root = phoneInsert(root, name, phone);
            cout << "Добавлено.\n";
            break;
        case 2:
            cout << "Имя: "; cin >> name;
            if (PhoneNode* f = phoneSearch(root, name)) {
                cout << f->name << ": ";
                for (size_t i = 0; i < f->phones.size(); i++)
                    cout << (i ? ", " : "") << f->phones[i];
                cout << endl;
            } else cout << "Не найдено.\n";
            break;
        case 3:
            cout << "Имя: "; cin >> name;
            root = phoneDelete(root, name);
            cout << "Удалено.\n";
            break;
        case 4:
            phoneInorder(root);
            break;
        }
    }
    phoneFree(root);
}

// ============================================================================
//             ЗАДАНИЕ 4 — Дерево интервалов (построение, обход, запрос)
// ============================================================================

struct IntervalNode {
    int l, r;
    IntervalNode *left, *right;
    IntervalNode(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {}
};

// Рекурсивное построение сбалансированного дерева из отсортированного массива
IntervalNode* buildIntervalTree(vector<pair<int,int>>& iv, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = (lo + hi) / 2;
    IntervalNode* nd = new IntervalNode(iv[mid].first, iv[mid].second);
    nd->left  = buildIntervalTree(iv, lo, mid - 1);
    nd->right = buildIntervalTree(iv, mid + 1, hi);
    return nd;
}

void ivPreorder(IntervalNode* nd) {
    if (!nd) return;
    cout << "[" << nd->l << "," << nd->r << "] ";
    ivPreorder(nd->left);
    ivPreorder(nd->right);
}
void ivInorder(IntervalNode* nd) {
    if (!nd) return;
    ivInorder(nd->left);
    cout << "[" << nd->l << "," << nd->r << "] ";
    ivInorder(nd->right);
}
void ivPostorder(IntervalNode* nd) {
    if (!nd) return;
    ivPostorder(nd->left);
    ivPostorder(nd->right);
    cout << "[" << nd->l << "," << nd->r << "] ";
}

int countContaining(IntervalNode* nd, int x) {
    if (!nd) return 0;
    int cnt = (nd->l <= x && x <= nd->r) ? 1 : 0;
    return cnt + countContaining(nd->left, x) + countContaining(nd->right, x);
}

void ivFree(IntervalNode* nd) {
    if (!nd) return;
    ivFree(nd->left);
    ivFree(nd->right);
    delete nd;
}

void task4() {
    cout << "\n========== ЗАДАНИЕ 4: Дерево отрезков (интервалы) ==========\n";
    int n;
    cout << "Введите количество интервалов: ";
    cin >> n;

    vector<pair<int,int>> iv(n);
    for (int i = 0; i < n; i++) {
        cout << "Интервал " << i + 1 << " (l r): ";
        cin >> iv[i].first >> iv[i].second;
    }

    sort(iv.begin(), iv.end());
    IntervalNode* root = buildIntervalTree(iv, 0, n - 1);
    cout << "Дерево построено рекурсивно.\n";

    cout << "\nПрямой обход:       "; ivPreorder(root);  cout << endl;
    cout << "Симметричный обход: ";   ivInorder(root);   cout << endl;
    cout << "Обратный обход:     ";   ivPostorder(root); cout << endl;

    int x;
    cout << "\nВведите точку X: ";
    cin >> x;
    cout << "Интервалов, содержащих " << x << ": " << countContaining(root, x) << endl;

    ivFree(root);
}

// ============================================================================
//       ЗАДАНИЕ 5 — Дерево отрезков (сумма, мин, макс, чёт/нечёт на отрезке)
// ============================================================================

class SegmentTree {
    int n;
    vector<int> arr;
    vector<long long> sumT;
    vector<int> minT, maxT, evenT, oddT;

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            sumT[v]  = arr[tl];
            minT[v]  = arr[tl];
            maxT[v]  = arr[tl];
            evenT[v] = (arr[tl] % 2 == 0) ? 1 : 0;
            oddT[v]  = 1 - evenT[v];
            return;
        }
        int tm = (tl + tr) / 2;
        build(2*v, tl, tm);
        build(2*v+1, tm+1, tr);
        sumT[v]  = sumT[2*v]  + sumT[2*v+1];
        minT[v]  = min(minT[2*v],  minT[2*v+1]);
        maxT[v]  = max(maxT[2*v],  maxT[2*v+1]);
        evenT[v] = evenT[2*v] + evenT[2*v+1];
        oddT[v]  = oddT[2*v]  + oddT[2*v+1];
    }

    long long qSum(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return sumT[v];
        int tm = (tl + tr) / 2;
        return qSum(2*v,   tl,   tm, l, min(r, tm))
             + qSum(2*v+1, tm+1, tr, max(l, tm+1), r);
    }
    int qMin(int v, int tl, int tr, int l, int r) {
        if (l > r) return INT_MAX;
        if (l == tl && r == tr) return minT[v];
        int tm = (tl + tr) / 2;
        return min(qMin(2*v, tl, tm, l, min(r,tm)),
                   qMin(2*v+1, tm+1, tr, max(l,tm+1), r));
    }
    int qMax(int v, int tl, int tr, int l, int r) {
        if (l > r) return INT_MIN;
        if (l == tl && r == tr) return maxT[v];
        int tm = (tl + tr) / 2;
        return max(qMax(2*v, tl, tm, l, min(r,tm)),
                   qMax(2*v+1, tm+1, tr, max(l,tm+1), r));
    }
    int qEven(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return evenT[v];
        int tm = (tl + tr) / 2;
        return qEven(2*v, tl, tm, l, min(r,tm))
             + qEven(2*v+1, tm+1, tr, max(l,tm+1), r);
    }
    int qOdd(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return oddT[v];
        int tm = (tl + tr) / 2;
        return qOdd(2*v, tl, tm, l, min(r,tm))
             + qOdd(2*v+1, tm+1, tr, max(l,tm+1), r);
    }

public:
    void init(vector<int>& a) {
        arr = a;  n = a.size();
        sumT.assign(4*n, 0);
        minT.assign(4*n, 0);
        maxT.assign(4*n, 0);
        evenT.assign(4*n, 0);
        oddT.assign(4*n, 0);
        build(1, 0, n - 1);
    }
    long long querySum (int l, int r) { return qSum (1, 0, n-1, l, r); }
    int       queryMin (int l, int r) { return qMin (1, 0, n-1, l, r); }
    int       queryMax (int l, int r) { return qMax (1, 0, n-1, l, r); }
    int       queryEven(int l, int r) { return qEven(1, 0, n-1, l, r); }
    int       queryOdd (int l, int r) { return qOdd (1, 0, n-1, l, r); }
    int       size()                  { return n; }
};

void task5() {
    cout << "\n========== ЗАДАНИЕ 5: Дерево отрезков (запросы) ==========\n";
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Введите " << n << " элементов: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree st;
    st.init(arr);
    cout << "Дерево отрезков построено.\n";

    while (true) {
        cout << "\n1-Сумма  2-Минимум  3-Максимум  4-Чёт/нечёт  0-Назад\nВыбор: ";
        int ch; cin >> ch;
        if (ch == 0) break;

        int a, b;
        cout << "a b (0-индексация): ";
        cin >> a >> b;
        if (a < 0 || b >= st.size() || a > b) { cout << "Некорректно.\n"; continue; }

        switch (ch) {
        case 1: cout << "Сумма: "    << st.querySum(a, b)  << endl; break;
        case 2: cout << "Минимум: "  << st.queryMin(a, b)  << endl; break;
        case 3: cout << "Максимум: " << st.queryMax(a, b)  << endl; break;
        case 4: cout << "Чётных: "   << st.queryEven(a, b)
                     << "  Нечётных: " << st.queryOdd(a, b) << endl; break;
        }
    }
}

// ============================================================================
//                 ЗАДАНИЕ 6 — 2D Range Tree (точки в прямоугольнике)
// ============================================================================

class RangeTree2D {
    int n;
    vector<pair<int,int>> pts;          // отсортированы по x
    vector<vector<int>>   tree;         // tree[v] — отсортированные y-координаты

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = { pts[tl].second };
            return;
        }
        int tm = (tl + tr) / 2;
        build(2*v, tl, tm);
        build(2*v+1, tm+1, tr);
        merge(tree[2*v].begin(), tree[2*v].end(),
              tree[2*v+1].begin(), tree[2*v+1].end(),
              back_inserter(tree[v]));
    }

    int query(int v, int tl, int tr, int l, int r, int ylo, int yhi) {
        if (l > r || tl > r || tr < l) return 0;
        if (l <= tl && tr <= r) {
            auto lo = lower_bound(tree[v].begin(), tree[v].end(), ylo);
            auto hi = upper_bound(tree[v].begin(), tree[v].end(), yhi);
            return (int)(hi - lo);
        }
        int tm = (tl + tr) / 2;
        return query(2*v, tl, tm, l, r, ylo, yhi)
             + query(2*v+1, tm+1, tr, l, r, ylo, yhi);
    }

public:
    void init(vector<pair<int,int>>& points) {
        pts = points;
        sort(pts.begin(), pts.end());
        n = pts.size();
        if (!n) return;
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    int countInRect(int xmin, int ymin, int xmax, int ymax) {
        if (!n) return 0;
        int l = (int)(lower_bound(pts.begin(), pts.end(),
                                  make_pair(xmin, INT_MIN)) - pts.begin());
        int r = (int)(upper_bound(pts.begin(), pts.end(),
                                  make_pair(xmax, INT_MAX)) - pts.begin()) - 1;
        if (l > r || l >= n) return 0;
        return query(1, 0, n - 1, l, r, ymin, ymax);
    }
};

void task6() {
    cout << "\n========== ЗАДАНИЕ 6: 2D Range Tree ==========\n";
    int n;
    cout << "Введите количество точек: ";
    cin >> n;

    vector<pair<int,int>> pts(n);
    cout << "Введите точки (x y):\n";
    for (int i = 0; i < n; i++)
        cin >> pts[i].first >> pts[i].second;

    RangeTree2D rt;
    rt.init(pts);

    int x1, y1, x2, y2;
    cout << "Введите прямоугольник (xmin ymin xmax ymax): ";
    cin >> x1 >> y1 >> x2 >> y2;

    cout << "Точек в прямоугольнике: " << rt.countInRect(x1, y1, x2, y2) << endl;
}

// ============================================================================
//                                  MAIN
// ============================================================================

int main() {
    srand((unsigned)time(0));

    while (true) {
        cout << "\n================ ГЛАВНОЕ МЕНЮ ================\n";
        cout << "1. BST (добавление, обход, высота, поиск, удаление)\n";
        cout << "2. Ближайший балл в BST\n";
        cout << "3. Телефонная книга (BST)\n";
        cout << "4. Дерево интервалов (построение, обход, подсчёт)\n";
        cout << "5. Дерево отрезков (сумма, мин, макс, чёт/нечёт)\n";
        cout << "6. 2D Range Tree (точки в прямоугольнике)\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        int ch; cin >> ch;

        switch (ch) {
            case 0: return 0;
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            default: cout << "Неверный выбор.\n";
        }
    }
}