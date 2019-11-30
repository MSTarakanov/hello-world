#ifndef QUEUE_H
#define QUEUE_H

#include "pokupka.h"
#include "card_pokupka.h"
#include <string>
#include <iostream>

using namespace std;

class queue;

class element
{
public:
    element()
    {
        next_element = nullptr;
    }
    bool operator == (element const &other)
    {
        return value->get_mounth() == other.value->get_mounth() && value->get_day() == other.value->get_day() && other.value->get_sum()==value->get_sum();
    }

   element *next_element;
   pokupka *value;
};


class iterat
{
  public:
    iterat(element *n)
    {
       current_element = n;
    }
    void move()
    {
        current_element = current_element->next_element;
    }
    pokupka *get_value()
    {
        return current_element->value;
    }

    bool operator == (iterat const &other)
    {
        if (this->current_element == other.current_element)
            return true;
        else return false;
    }

    bool operator != (iterat const &other)
    {
        return !(*this == other);
    }

    element *current_element;
};

class queue
{


public:
    queue();//работает
    queue(const queue &q);//работает
    ~queue();

    void enqueue(pokupka &new_pokupka);//работает

    void dequeue();//работает

    void clear();//работает

    int size() const;//работает

    pokupka *getPok(int n) const;

    pokupka *peek(int n) const;

    void file_write(std::string fileName);//работает

    bool file_read(std::string fileName);//работает

    int sum_period(int mounth1, int day1,int mounth2,int day2); //работает

    int right_vvod();
    //pokupka peek() const;//работает
    iterat start() const;
    iterat end() const;
    bool operator==(queue const &s);
    bool operator!=(queue const &s);

    element *_last;
    element *_first;
};

#endif // QUEUE_H
