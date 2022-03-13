#include <iostream>

char chariput();

struct DoubleDirectedList
{
    int data;
    DoubleDirectedList* Previous;
    DoubleDirectedList* Next;
};

DoubleDirectedList* HEAD;
int ListSize = 0;

void ListInitialize()
{
    HEAD = new DoubleDirectedList();
    HEAD->Next = NULL;
}

bool IsEmpty()
{
    if (HEAD->Next == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AddElement(int index)
{
    DoubleDirectedList* Node = new DoubleDirectedList();

    if (IsEmpty())
    {
        std::cout << "Ваш список пуст, но сейчас мы это исправим\n";
        HEAD->Next = Node;
        Node->data = rand() % 101;
        Node->Next = Node;
        Node->Previous = Node;
        ListSize++;
    }
    else if(index > ListSize)
    {
        std::cout << "Ваш индекс больше, чем ко-во элементов списка. Добавил в конец\n";
        DoubleDirectedList* ptr = new DoubleDirectedList();
        ptr = HEAD->Next;

        do
        {
            if (ptr->Next == HEAD->Next)
            {                
                Node->Previous = ptr;
                Node->Next = HEAD->Next;
                Node->data = rand() % 101;
                ptr->Next = Node;
                (HEAD->Next)->Previous = Node;
                break;
            }
            ptr = ptr->Next;

        } while (Node->Next != HEAD->Next);
        ptr = NULL;

        ListSize++;
       
    }
    else
    {
        int counter = 0;
        DoubleDirectedList* ptr = HEAD;
        if (index == 0)
        {
            do
            {
               ptr = ptr->Next;

            } while (ptr->Next!=HEAD->Next);

            (HEAD->Next)->Previous = Node;
            Node->Next = HEAD->Next;
            Node->Previous = ptr;
            ptr->Next = Node;
            HEAD->Next = Node;
            Node->data = rand() % 101;
            ptr = NULL;
        }
        else
        {
            while (counter < index)
            {
                ptr = ptr->Next;
                counter++;
            }
            Node->Previous = ptr;
            Node->Next = ptr->Next;
            (ptr->Next)->Previous = Node;
            ptr->Next = Node;

            Node->data = rand() % 101;
            ptr = NULL;
        }
        
        
        ListSize++;
    }
}
void pop(int index)
{
    if (IsEmpty())
    {
        std::cout << "Ваш список пуст\n";
        return;
    }
    int counter = 0;
    DoubleDirectedList* ptr = HEAD;

    index = index % ListSize;
    if (index == 0)
    {
        do
        {
            ptr = ptr->Next;

        } while (ptr->Next != HEAD->Next);

        HEAD->Next = (HEAD->Next)->Next;
        delete(ptr->Next);
        ptr->Next = HEAD->Next;
        (HEAD->Next)->Previous = ptr;
        ptr = NULL;
    }
    else
    {
        while (counter < index)
        {
            ptr = ptr->Next;
            counter++;
        }
        DoubleDirectedList* temp = ptr->Next;
        ((ptr->Next)->Next)->Previous = ptr;
        ptr->Next = (ptr->Next)->Next;
        delete(temp);

        ListSize--;
    }  
}

void SearchElement(int element)
{
    DoubleDirectedList* ptr = HEAD->Next;

    char choice;
    bool elementFound = false;
    int counter = 0;

    std::cout << "f - для прямого обхода\nr - для обратного обхода\n";    
    choice = chariput();
    switch (choice)
    {
    case'f':
        do
        {
            if (ptr->data == element)
            {
                std::cout << "Ваш элемент найден под индексом: " << counter << std::endl;
                elementFound = true;
            }
            ptr = ptr->Next;
            counter++;
        } while (ptr!=HEAD->Next);

        break;

    case 'r':
        do
        {
            if (ptr->data == element)
            {
                std::cout << "Ваш элемент найден под индексом: " << counter << std::endl;
                elementFound = true;
            }
            ptr = ptr->Previous;
            counter++;
        } while (ptr != HEAD->Next);
        break;

    default:
        break;
    }

    if (!elementFound)
    {
        std::cout << "Ваш элемент не найден!\n";
    }
}

void ShowListForwardDir()
{
    if (IsEmpty())
    {
        std::cout << "Список пуст\n";
        return;
    }
    DoubleDirectedList* ptr = HEAD->Next; // создаем копию, чтобы не портить текущую вершину
    std::cout << "Ваш список:\n";
    do
    {
        std::cout << ptr->data << " ";
        ptr = ptr->Next;
    } while (ptr != HEAD->Next);
    ptr = NULL;
    std::cout << std::endl << std::endl;
}
void ShowListReverseDir()
{
    if (IsEmpty())
    {
        std::cout << "Список пуст\n";
        return;
    }
    DoubleDirectedList* ptr = HEAD->Next; // создаем копию, чтобы не портить текущую вершину
    std::cout << "Ваш список:\n";
    do
    {
        std::cout << ptr->data << " ";
        ptr = ptr->Previous;
    } while (ptr != HEAD->Next);
    ptr = NULL;
    std::cout << std::endl << std::endl;
}

char chariput()
{
    char iput;
    while ((!(std::cin >> iput) || (std::cin.peek() != '\n')))
    {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "ошибка!" << std::endl;
    }
    return iput;
}
int intiput()
{
    int iput;
    while ((!(std::cin >> iput) || (std::cin.peek() != '\n')))
    {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "ошибка!" << std::endl;
    }
    return iput;
}


int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    char choice;
    int index;
    int element;
    bool working = true;

    ListInitialize();

    while (working)
    {
        std::cout
            << "Введите, что вы хотите сделать:\n"
            << "1)Добавить элемент\n"
            << "2)Удалить элемент\n"
            << "3)Найти элемент\n";

        choice = chariput();
        char direction;

        switch (choice)
        {
        case '1':
            std::cout << "Введите индекс\n";
            index = intiput();
            AddElement(index);
            std::cout << "f - прямое направление\nr - обратное направление\n";
            direction = chariput();

            if (direction == 'f')
            {
                ShowListForwardDir();
                break;
            }
            else if (direction == 'r')
            {
                ShowListReverseDir();
                break;
            }         
            else
            {
                std::cout << "Вы ввели что-то не то!\n";
                break;
            }
        case '2':
            std::cout << "Введите индекс\n";
            index = intiput();
            pop(index);
            std::cout << "f - прямое направление\nr - обратное направление\n";
            direction = chariput();

            if (direction == 'f')
            {
                ShowListForwardDir();
                break;
            }
            else if (direction == 'r')
            {
                ShowListReverseDir();
                break;
            }
            else
            {
                std::cout << "Вы ввели что-то не то!\n";
                break;
            }
        case '3':
            std::cout << "Введите интересующий вас элемент:\n";
            element = intiput();
            SearchElement(element);     
            break;
            
        default:
            std::cout << "Работа цикла завершена!\n";
            working = false;
            break;
        }
    }
}
