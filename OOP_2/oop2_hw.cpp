#include <iostream>
#include <stdlib.h>

using namespace std;

#define owner_size 21
#define date_size 11

class Data
{
private:
    int number;
    char *owner;
    char *date;
    int sum;

public:
    Data()
    {
        srand(time(NULL));
        number = rand();
        owner = new char[owner_size];
        date = new char[date_size];
        sum = rand();
        cout << "Default initialization" << endl;
    }
    Data(int number1, const char owner1[], const char date1[], int sum1)
    {
        number = number1;
        owner = new char[owner_size];
        date = new char[date_size];
        sum = sum1;

        for (int i = 0; i < owner_size; i++)
        {
            if (i == owner_size - 1)
            {
                owner[i] = 0;
                break;
            }
            owner[i] = owner1[i];
            if (owner1[i] == 0)
                break;
        }
        for (int i = 0; i < date_size; i++)
        {
            date[i] = date1[i];
            if (i == date_size - 1)
            {
                date[i] = 0;
                break;
            }
        }
        cout << "Regular initialization" << endl;
    }

    Data(const Data &Data1)
    {
        number = Data1.number;
        owner = new char[owner_size];
        date = new char[date_size];
        sum = Data1.sum;

        for (int i = 0; i < owner_size; i++)
        {
            if (i == owner_size - 1)
            {
                owner[i] = 0;
                break;
            }
            owner[i] = Data1.owner[i];
            if (Data1.owner[i] == 0)
                break;
        }
        for (int i = 0; i < date_size; i++)
        {
            date[i] = Data1.date[i];
            if (i == date_size - 1)
            {
                date[i] = 0;
                break;
            }
        }
        cout << "Copy constructor" << endl;
    }

    ~Data()
    {
        delete[] owner;
        delete[] date;
        cout << "Destructor" << endl;
    }

    Data &operator=(const Data &Data1)
    {
        if (this != &Data1)
        {
            number = Data1.number;
            sum = Data1.sum;

            for (int i = 0; i < owner_size; i++)
            {

                if (i == owner_size - 1)
                {
                    owner[i] = 0;
                    break;
                }
                owner[i] = Data1.owner[i];
                if (Data1.owner[i] == 0)
                    break;
            }
            for (int i = 0; i < date_size; i++)
            {
                date[i] = Data1.date[i];
                if (i == date_size - 1)
                {
                    date[i] = 0;
                    break;
                }
            }
        }
        cout << "Assignment operator" << endl;
        return *this;
    }
    void print()
    {   cout << "_______________________________" << endl;
        cout << "Number: " << number << endl
             << "Owner: " << owner << endl
             << "Date: " << date << endl
             << "Sum: " << sum << endl;
        cout << "_______________________________" << endl << endl;
    }
};

class List
{
private:
    struct elem
    {
        Data inf;
        elem *next;
        elem *prev;
    };
    elem *first;
    elem *last;

public:
    List()
    {
        first = NULL;
        last = NULL;
    }

    ~List()
    {
        elem *tmp;
        while (first != NULL)
        {
            tmp = first;
            first = first->next;
            delete tmp;
        }
    }
    void push_front(Data x)
    {
        elem *elem1 = new elem;
        elem1->inf = x;
        elem1->prev = NULL;
        elem1->next = first;
        if (first != NULL)
            first->prev = elem1;
        first = elem1;
        if (last == NULL)
            last = elem1;
    }
    void push_back(Data x)
    {
        elem *elem1 = new elem;
        elem1->inf = x;
        elem1->next = NULL;
        elem1->prev = last;
        if (last != NULL)
            last->next = elem1;
        last = elem1;
        if (first == NULL)
            first = elem1;
    }
    Data front()
    {
        return first->inf;
    }
    Data back()
    {
        return last->inf;
    }
    void pop_front()
    {
        if (first != NULL)
        {
            elem *elem1 = first;
            first = first->next;
            if (first != NULL)
            {
                first->prev = NULL;
            }
            else
            {
                last = NULL;
            }
            delete elem1;
        }
    }
    void pop_back()
    {
        if (last != NULL)
        {
            elem *elem1 = last;
            last = last->prev;
            if (last != NULL)
            {
                last->next = NULL;
            }
            else
            {
                first = NULL;
            }
            delete elem1;
        }
    }
    void insert(int p, Data x)
    {
        elem *tmp = first;
        while ((p > 0) && tmp != NULL)
        {
            tmp = tmp->next;
            p--;
        }
        if (tmp == first)
            push_front(x);
        else if (tmp == NULL)
            push_back(x);
        else
        {
            elem *elem1 = new elem;
            elem1->inf = x;
            elem1->next = tmp;
            elem1->prev = tmp->prev;
            elem1->prev->next = elem1;
            tmp->prev = elem1;
        }
    }
    void erase(int p)
    {
        elem *tmp = first;
        while ((p > 0) && tmp != NULL)
        {
            tmp = tmp->next;
            p--;
        }
        if (tmp != NULL)
        {
            if (tmp == first)
                pop_front();
            else if (tmp == last)
                pop_back();
            else
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                delete tmp;
            }
        }
    }

    bool empty()
    {
        return first == NULL;
    }

    int size()
    {
        int all = 0;
        elem *elem1 = first;
        while (elem1 != NULL)
        {
            all++;
            elem1 = elem1->next;
        }
        return all;
    }

    void print()
    {
        elem *elem1 = first;
        if (empty())
            cout << "The list is empty" << endl;
        else
            for (int i = 0; i < size(); i++)
            {
                (elem1->inf).print();
                elem1 = elem1->next;
            }
    }
};

int main()
{
    List data;
    cout << data.size() << endl;
    Data elem1(123456, "Alterman Lev", "4.11.2003", 100000);
    Data elem2(456789, "Godunova Elizaveta", "06.11.2003", 100);

    data.push_front(elem1);
    data.push_front(elem2);
    data.print();

    data.push_back(elem1);
    data.pop_front();
    cout << data.size() << endl;

    data.insert(1, elem2);
    data.print();
    data.erase(2);

    data.print();
}