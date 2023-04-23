#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace sf;
using namespace std;

bool alredy(int a[], int size, int search)
{
    for (int k(0); k < size; k++)
    {
        if (a[k] == search)return true;
    }

    return false;
}

void sort(int a[], int size)
{
    int tmp;
    bool moved = false;

    for (int i(0); i < size - 1; i++)
    {
        moved = false;
        for (int j(0); j < size - i - 1; j++)
        {

            if (a[j] > a[j + 1])
            {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                moved = true;
            }

            if (moved)break;

        }

    }

}

int biggest(int array[], int size, int* factor)
{
    int max = 0;

    for (int k(0); k < size - *factor; k++)
    {
        if (array[k] > max)max = array[k];
    }

    return max;
}

void move(int array[], int size, int* factor, int* position, bool* sorted)
{
    int max = biggest(array, size, factor);

    for (int k(0); k < size - *factor; k++)
    {
        if (array[k] == max && array[k] > array[k + 1])
        {
            int tmp = array[k];
            array[k] = array[k + 1];
            array[k + 1] = tmp;
            *position = k;
            break;
        }
    }

    if (0 == max)*sorted = true;

    if (*factor < size && array[size - *factor] == max)*factor = *factor + 1;

}

void blend(int array[], const int size)
{
    for (int k(0); k < size; k++)
    {
        int random = rand() % size;

        int tmp = array[k];

        array[k] = array[random];
        array[random] = tmp;
    }
}

int main()
{
    int width = 1200, height = 1200;

    RenderWindow window(VideoMode(width, height), "Sorting");

    int x(0), y(20), rectangle_y(0), rectangle_x(1);

    int size = width / rectangle_x;

    int* array = new int[size];
    int factor = 0;

    Clock clock;
    srand(time(0));

    double timer(0), delay(0.01);

    int copySize = size;

    for (int k(0); k < copySize; k++)
    {     
        array[k] = --size;     
    }


    size = copySize;

    blend(array, copySize);

    int position = 0;
    bool sorted = false;
    RectangleShape* rect = new RectangleShape[size];
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        window.clear();

        for (int i(0); i < size; i++)
        {
            timer += time;
            rectangle_y = array[i];

            y = height - rectangle_y;

            rect[i].setSize(Vector2f(rectangle_x, rectangle_y));
            rect[i].setFillColor(Color::Red);

            if (timer > delay)
            {
                move(array, size, &factor, &position, &sorted);
                timer = 0;
            }

            if (!sorted)rect[position].setFillColor(Color::Green);
            rect[i].setPosition(x, y);

            window.draw(rect[i]);

            x += rectangle_x;
        }

        x = 0;

        window.display();
    }
    factor = 0;

   

}




