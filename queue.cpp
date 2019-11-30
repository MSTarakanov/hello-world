#include "queue.h"
#include <stdio.h>
#include <iostream>
#include "pokupka.h"
#include <fstream>
#include <stdlib.h>
#include <assert.h>

using namespace std;


queue::queue()
{
 _last = _first = nullptr;
}

queue::queue(const queue &q)
{
if (q._first != nullptr && q._last !=nullptr)
{
    _first= q._first;
    _last= q._last;
    cout<<"q was qopied"<<endl;
}
else
{
    _first=_last=nullptr;
}
}

queue::~queue()
{

}

void queue::enqueue(pokupka &new_pokupka)
{
// int sum = new_pokupka.getsum();
// int mounth = new_pokupka.getmounth();
// int day = new_pokupka.getday();
 element *n;
 n = new element();


 n ->value = &new_pokupka;
 if (_first == nullptr)
    {
//     n->value.setsum(sum);
//     n->value.setmounth(mounth);
//     n->value.setday(day);
        n->next_element=nullptr;
        _first = n;
        _last = n;
        cout<<"first element is added"<<endl;
    }
    else
    {

//     n->value.setsum(sum);
//     n->value.setmounth(mounth);
//     n->value.setday(day);
         n->next_element = nullptr;
         _last->next_element=n;
         _last = n;
         cout<<"element is added"<<endl;
    }
 if (new_pokupka.get_kind()==WithCard)
 {
     card_pokupka *num1 = dynamic_cast<card_pokupka*>(&new_pokupka);
     if (!num1){cout<<"error";}
 }
}

void queue::dequeue()
{
    if (_first != nullptr)
    {
        element *d = _first;
        _first=_first->next_element;
        delete d;
        cout<<"element has been deleted"<<endl;
    }
    else
    {
        cout<<"nothing to delete"<<endl;
    }
}


void queue::clear()
{
    element *q = _first;
    while (_first !=nullptr)
    {
        _first = _first->next_element;
        delete q;
        q = _first;
        cout<<"-1"<<endl;
    }
    if (_first==nullptr)
        cout<<"q is empty!"<<endl;
}




int queue::size() const
{
    int i = 0;
    if (_first !=nullptr)
    {
        element *n = _first;
        while (n!=nullptr)
        {
            i++;
            n=n->next_element;
        }
    }
    else
    {cout<<"u have no elements"<<endl;}

    return i;
}

void queue::file_write(std::string fileName)
{
    int k=1;
    ofstream file (fileName);

    if (file.is_open())
    {
        //file <<"Совершенные покупки:"<<endl;
        element *n = _first;
        if (n!= nullptr)
       {
            while (n!=nullptr)
            {
                if (n->value->get_kind()==WithoutCard)
                {
                    file << "WithoutCard ";
                    //file << "WithoutCard"<< ": ";
                }
                else
                    file << "WithCard ";
                    //file << "   WithCard"<< ": ";
                file << n->value->get_day() << " " << n->value->get_mounth() << " " << n->value->get_sum();
               // file << n->value->getday() << "." << n->value->getmounth() << " sum: " << n->value->getsum();
                if (n->value->get_kind()== WithCard)
                {
                    card_pokupka *num = dynamic_cast<card_pokupka*>(this->peek(k));
                    file<<" " << num->get_cardnumber()<<endl;
                    //file<<" cardnumber:" << num->getcardnumber()<<endl;

                }
                else
                {
                    file<<endl;
                }
                n = n->next_element;
                k++;

            }
       }
       else
       {
        file.close();
        return;
       }
    file.close();
    }
}

bool queue::file_read(std::string fileName)
{
    string kind;
    ifstream file(fileName);
    if (file.is_open())
    {
        _first=nullptr;
        int mounth,day,sum;
        string cardnumber;
        while(file >> kind >> day >> mounth >> sum)
        {
            if (kind == "WithoutCard")
            {
                pokupka *num = new pokupka(day,mounth,sum);
                this->enqueue(*num);
            }
            else if (kind == "WithCard")
            {
                file >> cardnumber;
                pokupka *num = dynamic_cast<pokupka*>(new card_pokupka(day,mounth,sum,cardnumber));
                this->enqueue(*num);
            }

        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }


}

iterat queue::start() const
{
return iterat(_first);
}

iterat queue::end() const
{
iterat a(nullptr);
return a;
}

pokupka *queue::peek(int n) const
{
    assert(n <= this->size());
    int num_iter = 1;
    iterat i = this->start();
    while(i!=this->end() && num_iter<n)
    {
        i.move();
        num_iter++;
    }
    return i.get_value();
}

pokupka *queue::getPok(int n) const
{
    pokupka *k= this->peek(n);
    return k;
}
int queue::sum_period( int day1,int mounth1, int day2, int mounth2)
{

    if (_first!=nullptr)
    {
        element *n = _first;
        n = new element();
        n = _first;
        //bool flag = false;
        int sum_period = 0;

        while(n!=nullptr)
        {
            //cout<<endl<<day1<<"."<<mounth1<<" "<<n->value->getday()<<"."<<n->value->getmounth()<<" "<<day2<<"."<<mounth2<<endl;
            if (mounth1<n->value->get_mounth() && n->value->get_mounth()<mounth2)
            {   //cout<<"mounth1<n->value->getmounth()<mounth2"<<endl;
                sum_period= sum_period + n->value->get_sum();}
            else if (mounth1 == n->value->get_mounth() && n->value->get_mounth()== mounth2)
            {
                if (day1<=n->value->get_day() && n->value->get_day()<=day2)
                    {sum_period= sum_period + n->value->get_sum();}
            }
            else if (mounth1==n->value->get_mounth())
            {
                if (day1<=n->value->get_day())
                    {sum_period= sum_period + n->value->get_sum();}
            }
            else if (n->value->get_mounth()==mounth2)
            {
                if (n->value->get_day()<=day2)
                    {sum_period= sum_period + n->value->get_sum();}
            }
            n = n->next_element;
        }
        return sum_period;
    }
    else
        return 0;

}

int queue::right_vvod()
{
int count = 0;
if (_first!=nullptr)
    {
    element *n = _first;
    n = new element();
    n = _first;

    while (n!=nullptr && n->next_element!=nullptr)
        {
            if (n->value->get_mounth()>n->next_element->value->get_mounth())
                {count++;}
            else if (n->value->get_mounth()==n->next_element->value->get_mounth())
            {
                if (n->value->get_day()>n->next_element->value->get_day())
                    {count++;}
            }
            n = n->next_element;

        }

    cout<<"u had "<<count<<" mistakes"<<endl;
    }
else
        {
            cout<<"error: u have no queue"<<endl;
        }

return count;

}





bool queue::operator==(queue const  &s)
{
    if (s._first != nullptr && this->size() == s.size())
    {
        element *a = new  (element);
        element *b = new  (element);
        a = this->_first;
        b = s._first;
        bool right = false;
        while (a != nullptr && b!= nullptr)
        {
            if (a==b)
            {
                right = true;
                a = a->next_element;
                b = b->next_element;
            }
            else
            {
                right = false;
                delete a;
                delete b;
                return right;
            }
        }
        if (right == true)
        {
            delete a;
            delete b;
            return right;
        }
    }
    return false;
}

bool queue::operator!=(queue const  &s)
{
    if (s._first != nullptr && this->size() == s.size())
    {
        element *a = new  (element);
        element *b = new  (element);
        a = this->_first;
        b = s._first;
        bool right = false;
        while (a != nullptr && b!= nullptr)
        {
            if (a==b)
            {
                right = true;
                a = a->next_element;
                b = b->next_element;
            }
            else
            {
                right = false;
                delete a;
                delete b;
                return right;
            }
        }
        if (right == true)
        {
            delete a;
            delete b;
            return right;
        }
    }
    return false;
}
