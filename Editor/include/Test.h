





#pragma once
#include <stack>
#include <deque>
#include <cstdio>
#include "Input.h"

static int idCounter = 0;

struct Ent
{
    int id;
    int p_x, p_y;

    Ent(int x, int y)
        : p_x(x), p_y(y), id(idCounter++) {}

    void Print()
    {
        //printf("Printing Ent with id:%d\n", id);
    }
};

class Box
{
public:
    Box(int p_x, int p_y, int p_width, int p_height)
        : x(p_x), y(p_y), width(p_width), height(p_height) {}

    int x, y;
    int width, height;
    std::stack<Ent*> leftSide;
    std::stack<Ent*> rightSide;
    std::deque<Ent*> inside;

    void addEnt(Ent* ent)
    {
        if (ent->p_x < x)
            leftSide.push(ent);
        else if (ent->p_x > x + width)
            rightSide.push(ent);
        else
            inside.push_back(ent);
    }

    void Update()
    {
        checkLeft();
        checkRight();

        for (auto& ent : inside)
            ent->Print();

        if (Input::IsKeyPressed(GLFW_KEY_A))
            x -= 1;
        if (Input::IsKeyPressed(GLFW_KEY_D))
            x += 1;
    }

    bool checkLeft()
    {
        bool moved = false;
        while (!leftSide.empty() && leftSide.top()->p_x >= x)
        {
            inside.push_back(leftSide.top());
            leftSide.pop();
            moved = true;
        }
        return moved;
    }

    bool checkRight()
    {
        bool moved = false;
        while (!rightSide.empty() && rightSide.top()->p_x <= x + width)
        {
            inside.push_back(rightSide.top());
            rightSide.pop();
            moved = true;
        }
        return moved;
    }
};
