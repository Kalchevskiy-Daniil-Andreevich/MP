#include <iostream>
#include <vector>
#include <limits>
#include <list>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const int INF = std::numeric_limits<int>::max(); // бесконечность

// функция, которая проверяет есть ли число в векторе
bool isInVector(vector<int> v, int e)
{
    return find(v.begin(), v.end(), e) != v.end();
}

// функция, которая считает факториал
int factorial(int i)
{
    if (i == 0) return 1;
    else return i * factorial(i - 1);
}

// Класс, который хранит и обрабатывает матрицу
class Matrix
{
public:
    int s; // размерность матрицы
    // конструктор класса принимает вектор векторов
    Matrix(vector<vector<int>> matrix)
    {
        this->matrix = matrix;
        this->s = matrix.size();
        this->generateMatrixT();
    }

    // метод, который выводит матрицу на экран
    void print()
    {
        cout << "Матрица затрат: " << '\n';
        for (auto it = this->matrix.begin(); it != this->matrix.end(); ++it)
        {
            for (const auto& i : *it)
            {
                cout << setw(6); // используется для форматирования вывода
                if (i == INF) cout << '-'; // вместо максимального значения int выводим тире
                else cout << i;
            };
            cout << '\n';
        }
        cout << '\n' << '\n';
    }

    // метод записи матрицы в файл
    void write()
    {
        ofstream out("matrix.txt");
        if (out.is_open())
        {
            out << this->matrix.size() << '\n';
            for (auto it = this->matrix.begin(); it != this->matrix.end(); ++it)
            {
                for (const auto& i : *it)
                {
                    if (i == INF) out << 0;
                    else out << i;
                    out << ' ';
                };
                out << '\n';
            }
        }
        out.close();
    }

    // метод, который позволяет получить значение в строке str и столбце stb
    int get(int str, int stb)
    {
        return this->matrix[str][stb];
    }

    // функция получения нижней оценки
    int getH(vector<int> strs, vector<int> stbs)
    {
        int H1 = this->findMinSum(this->matrix, strs, stbs);
        int H2 = this->findMinSum(this->matrixT, stbs, strs);
        return max(H1, H2);
    }

    // метод получения верхней оценки
    int getV(vector<int> last_nodes, int current_point)
    {
        int V1 = 0;
        for (int i = 0; i < this->s; ++i)
        {
            if (!isInVector(last_nodes, i) && i != current_point)
            {
               V1 += this->matrix[current_point][i];
                last_nodes.push_back(current_point);
                current_point = i;
            }
        }
        V1 += this->matrix[current_point][0];
        return V1;
    }

private:
    vector<vector<int>> matrix, matrixT;

    // генерация транспонированной матрицы
    void generateMatrixT()
    {
        this->matrixT = vector<vector<int>>(this->s);
        for (int i = 0; i < s; ++i)
        {
            for (int j = 0; j < s; ++j)
            {
                matrixT[i].push_back(matrix[j][i]);
            }
        }
    }

    // метод, который занимается поиском минимальной суммы элементов в матрице,
    // кроме строк strs и столбцов stbs
    int findMinSum(vector<vector<int>> matrix, vector<int> strs, vector<int> stbs)
    {
        int sum = 0;
        int str_pos = 0;
        for (auto it = matrix.begin(); it != matrix.end(); ++it)
        {
            if (!isInVector(strs, str_pos))
            {
                int stb_pos = 0;
                int m = INF;
                for (const auto& i : *it)
                {
                    if (i < m && !isInVector(stbs, stb_pos)) m = i;
                    ++stb_pos;
                };
                sum += m;
            }
            ++str_pos;
        }
        return sum;
    }
};


// класс, который отвечает за вершину
class Node
{
public:
    int V; // Верхняя оценка
    int H; // Нижняя оценка

    // конструктор принимает список предыдущих городов, номер города
    // сумму переходов до этого города и указатель на матрицу
    Node(vector<int> last_nodes, int node, int sum_per, Matrix* matrix)
    {
        // присваиваем полям нужные значения
        this->last_nodes = last_nodes;
        this->node = node;
        this->node_quantity = matrix->s;
        this->matrix = matrix;

        this->sum_per = sum_per;

        // Если это не первая вершина, то считаем сумму переходов
        if (this->last_nodes.size() > 0)
        {
            this->sum_per += this->matrix->get(last_nodes.back(), this->node);
        }

        vector<int> strs;
        vector<int> stbs;

        // генерируем строки и столбцы, которые нужно вычеркнуть,
        // так как эти города уже посещены
        for (int i = 0; i < this->last_nodes.size(); ++i)
        {
            strs.push_back(this->last_nodes[i]);
            if (i + 1 < this->last_nodes.size())
                stbs.push_back(this->last_nodes[i + 1]);
            else
                stbs.push_back(this->node);
        }

        // получаем верхнюю и нижнюю оценки
        this->H = this->sum_per + this->matrix->getH(strs, stbs);
        this->V = this->sum_per + this->matrix->getV(last_nodes, node);
    }

    // метод, который возвращает список следующих вершин
    list<Node> getNextNodes()
    {
        list<Node> nodes;
        this->last_nodes.push_back(this->node);
  for (int i = 0; i < this->node_quantity; ++i)
        {
            if (!isInVector(this->last_nodes, i))
            {
                nodes.push_back(Node(this->last_nodes, i, this->sum_per, &(*this->matrix)));
            }
        }
        return nodes;
    }

    // печать текущего маршрута
    void print()
    {
        for (int i : this->last_nodes)
        {
            cout << i + 1 << " -> ";
        }
        cout << 1 << " Длина " << this->V << '\n';

        cout << "Матрица переходов: " << endl;
        vector<vector<int>> m;
        this->last_nodes.push_back(0);
        for (int i = 0; i < this->last_nodes.size() - 1; ++i)
        {
            vector<int> str;
            for (int j = 0; j < this->last_nodes.size() - 1; ++j)
                str.push_back(0);
            m.push_back(str);
        }
        for (int i = 0; i < this->last_nodes.size() - 1; ++i)
        {
            m[this->last_nodes[i]][this->last_nodes[i + 1]] = 1;
        }
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            for (const auto& i : *it)
            {
                cout << setw(6);
                cout << i;
            };
            cout << '\n';
        }

    }

private:
    vector<int> last_nodes;
    int node;
    Matrix* matrix;
    int node_quantity;
    int sum_per;
};

// класс, который содержит список вершин и
// манипулирует с ним
class Container
{
public:
    list<Node> nodes;
    int quantity;
    int r;
    int pr;

    // если pr = 1, то будет печаться промежуточная информация
    Container(int pr)
    {
        this->quantity = 0;
        this->r = INF;
        this->pr = pr;
    }

    // добавляем вершину и пересчитываем рекорд
    void add(Node node)
    {
        if (this->r >= node.V)
        {
            this->r = node.V;
        }
        nodes.push_back(node);
        ++this->quantity;
        this->newScreen();
    }

    // добавляем несколько
    void addSome(list<Node> nodes)
    {
        for (Node& n : nodes)
        {
            this->add(n);
        }
    }

    // удаляем текущие вершины и присваиваем новые
    void changeNodes(list<Node> nodes)
    {
        this->quantity = 0;
        this->nodes = {};
        this->addSome(nodes);
    }
// удаляем вершину по итератору
    list<Node>::iterator del(list<Node>::iterator itr)
    {
        --this->quantity;
        this->newScreen();
        return nodes.erase(itr);
    }

    // выводим на экран рекорд и количество вершин
    void newScreen()
    {
        if (pr == 1)
        {
            cout << "\033[F";
            cout << "\033[F";
            cout << "\rРекорд:" << setw(20) << this->r << endl;
            cout << "\rКоличество вершин:" << setw(6) << this->quantity << endl;
        }
    }
};

int Nodes()
{
    srand(time(0)); // генерируем матрицу случайно (каждый раз новую)
    system("chcp 1251 > nul"); // для того, чтобы программа выводила русский текст
    setlocale(0, "rus");
    int s;

    // запрашиваем у пользователя настройки
    cout << "Ввести, сгенерировать или считать из файла (0/1/2)?: ";
    int g;
    cin >> g;

    if (g != 0 && g != 1 && g != 2) return 1;

    if (g != 2)
    {
        cout << "Введите число городов: ";
        cin >> s;

        if (s < 3)
        {
            cout << "Слишком мало городов!";
            return 1;
        }
    }

    vector<vector<int>> m = {};
    if (g == 1)
    {
        int diap;
        cout << "Введите максимальные затраты." << endl <<
            "Диапазон затрат будет от 1 до введенного Вами числа: ";
        cin >> diap;
        for (int i = 0; i < s; ++i)
        {
            vector<int> str;
            for (int j = 0; j < s; ++j)
            {
                str.push_back(1 + (rand() % diap));
            }
            m.push_back(str);
        }
        for (int i = 0; i < s; ++i)
            m[i][i] = INF;
    }
    else if (g == 0)
    {
        // пользователь вводит матрицу
        cout << "Вводите матрицу построчно." << endl;
        for (int i = 0; i < s; ++i)
        {
            vector<int> str;
            for (int j = 0; j < s; ++j)
            {
                int d;
                cin >> d;
                str.push_back(d);
            }
            m.push_back(str);
        }
        for (int i = 0; i < s; ++i)
            m[i][i] = INF;
    }
    else
    {
        // читаем матрицу из файла
        ifstream in("matrix.txt");
        if (in.is_open())
        {
            int s;
            in >> s;
            for (int i = 0; i < s; ++i)
            {
                vector<int> str;
                for (int j = 0; j < s; ++j)
                {
                    int d;
                    in >> d;
                    str.push_back(d);
            }
                m.push_back(str);
            }
            for (int i = 0; i < s; ++i)
                m[i][i] = INF;
        }
        else
        {
            cout << "Ошибка! Где файл с матрицей???";
            exit(1);
        }
        in.close();
    }

    cout << "Выводить промежуточные результаты (0/1)? ";
    int pr;
    cin >> pr;

    Matrix matrix = Matrix(m); // создаем объект класса Matrix
    matrix.print(); // выводим на экран для проверки
    matrix.write(); // записываем матрицу в файл
    Node first = Node({}, 0, 0, &matrix); // первая вершина
    Container cont = Container(pr); // создаем контейнер
    cont.addSome(first.getNextNodes()); // делим первое множество и добавляем в контейнер

    int v = 0; // количество проверенных множеств

    double start = clock(); // запускаем измерение времени
    while (true)
    {
        list<Node>::iterator itr = cont.nodes.begin();
        list<Node> new_nodes;
        int i = 0;
        while (itr != cont.nodes.end()) // перебираем текущие вершины
        {
            // если нижняя оценка хуже рекорда, то удаляем вершину
            if (itr->H > cont.r && cont.nodes.size() != 1)
            {
                itr = cont.del(itr);
                ++v;
            }
            // иначе получаем список следующих вершин
            else
            {
                list<Node> nodes = itr->getNextNodes();
                new_nodes.insert(new_nodes.end(), nodes.begin(), nodes.end());
                ++itr;
            }
            ++i;
        }
        // если осталась 1 вершина и новых нет, то выходим из цикла
        if (cont.quantity == 1 && new_nodes.size() == 0)
            break;
        cont.changeNodes(new_nodes);

    }
    double t = (clock() - start) / CLOCKS_PER_SEC; // конец измерения времени

    cout << endl;
    cout << "Ответ:" << endl; // печатаем ответ
    cont.nodes.front().print();

    cout << '\n';

    int f = factorial(matrix.s - 1);
    int p = (1 - (float)v / f) * 100;

    // выводим дополнительную информацию
    cout << "Время работы: " << t << "сек." << endl;
    cout << "Всего проверено вариантов: " << v << endl;
    cout << "Вариантов полного перебора: " << f << endl;
    cout << "Метод ветвей и границ перебирает примерно на " << p << "% меньше вариантов.";

    return 0;
}
