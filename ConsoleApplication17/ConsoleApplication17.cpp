#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

class Vector
{
    unsigned int size;
    unsigned int capacity;
    int* data;

public:
    Vector() : size(0), capacity(10), data(nullptr)
    {
        data = new int[capacity];
    }

    Vector(unsigned int capacity)
    {
        if (capacity < 10)
        {
            capacity = 10;
        }
        this->capacity = capacity;
        data = new int[capacity];
    }

    ~Vector()
    {
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

private:
    void EnsureCapacity()
    {
        if (size < capacity)
        {
            return;
        }

        capacity *= 2;

        int* temp = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

public:
    void PushBack(int value)
    {
        EnsureCapacity();
        data[size] = value;
        size++;
    }

    void PushFront(int value)
    {
        EnsureCapacity();
        for (int i = size; i > 0; i--)
        {
            data[i] = data[i - 1];
        }
        data[0] = value;
        size++;
    }

    void Clear()
    {
        size = 0;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }

    void Print() const
    {
        if (IsEmpty())
        {
            cout << "Vector is empty." << endl ;
            return;
        }

        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << "" << endl ;
    }

    unsigned int GetSize() const
    {
        return size;
    }

    unsigned int GetCapacity() const
    {
        return capacity;
    }

    void Insert(int value, unsigned int index)
    {
        if (index > size)
        {
            cerr << "Error: Index out of bounds." << endl ;
            return;
        }

        EnsureCapacity();

        for (int i = size; i > index; i--)
        {
            data[i] = data[i - 1];
        }

        data[index] = value;
        size++;
    }

    void RemoveByIndex(unsigned int index)
    {
        if (index >= size)
        {
            cerr << "Error: Index out of bounds." << endl ;
            return;
        }

        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }

        size--;
    }

    void RemoveByValue(int value)
    {
        int* newData = new int[capacity];
        int newSize = 0;

        for (int i = 0; i < size; i++)
        {
            if (data[i] != value)
            {
                newData[newSize] = data[i];
                newSize++;
            }
        }

        delete[] data;
        data = newData;
        size = newSize;
    }

    void PopFront()
    {
        if (size > 0)
        {
            RemoveByIndex(0);
        }
    }

    void PopBack()
    {
        if (size > 0)
        {
            size--;
        }
    }

    int LastIndexOf(int value) const
    {
        for (int i = size - 1; i >= 0; i--)
        {
            if (data[i] == value)
                return i;
        }
        return -1;
    }

    void SortDesc()
    {
        sort(data, data + size, greater<int>());
    }

    void Shuffle()
    {
        random_shuffle(data, data + size);
    }

    void RandomFill()
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = rand() % 100;
        }
    }

    int GetElementAt(unsigned int index) const
    {
        if (index < size)
            return data[index];
        else
        {
            cerr << "Error: Index out of bounds." << endl ;
            return -1;
        }
    }

    Vector(const Vector& other)
    {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        copy(other.data, other.data + size, data);
    }

    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            copy(other.data, other.data + size, data);
        }
        return *this;
    }

    int& operator[](unsigned int index)
    {
        if (index < size)
            return data[index];
        else
        {
            cerr << "Error: Index out of bounds." << endl ;
            static int placeholder;  
            return placeholder;
        }
    }

    bool operator==(const Vector& other) const
    {
        if (size != other.size)
            return false;

        for (int i = 0; i < size; i++)
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const Vector& vec)
    {
        for (int i = 0; i < vec.size; i++)
        {
            os << vec.data[i] << " ";
        }
        return os;
    }
};

int main()
{
    setlocale(LC_ALL, "russian");
    Vector ar;

    for (int i = 0; i < 10; i++)
    {
        ar.PushBack(i * 10);
    }

    cout << "Исходный вектор:" << endl;
    ar.Print();

    int searchValue = ar.GetElementAt(3);
    int lastIndex = ar.LastIndexOf(searchValue);
    cout << "Последний индекс " << searchValue << ": " << lastIndex << "" << endl;

    ar.SortDesc();
    cout << "Вектор после сортировки по убыванию:" << endl;
    ar.Print();

    ar.Shuffle();
    cout << "Вектор после перемешивания:" << endl;
    ar.Print();

    ar.RandomFill();
    cout << "Вектор после случайного заполнения:" << endl;
    ar.Print();

    unsigned int indexToAccess = 2;
    int elementAtIndex = ar.GetElementAt(indexToAccess);
    cout << "Элемент по индексу " << indexToAccess << ": " << elementAtIndex << "" << endl;

    Vector arCopy(ar);
    cout << "Скопированный вектор:" << endl;
    arCopy.Print();

    Vector arAssign;
    arAssign = ar;
    cout << "Присвоенный вектор:" << endl;
    arAssign.Print();

    if (ar == arCopy)
    {
        cout << "Вектор и его копия равны." << endl;
    }
    else
    {
        cout << "Вектор и его копия не равны." << endl;
    }

    cout << "Элементы, используя оператор[]:" << endl;
    for (unsigned int i = 0; i < ar.GetSize(); i++)
    {
        cout << ar[i] << " ";
    }
    cout << "" << endl;

    return 0;
}

