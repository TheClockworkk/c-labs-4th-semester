// header.h: включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта
//

#pragma once

#include "targetver.h"
#include "Controls.h"
#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
// Файлы заголовков среды выполнения C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#define MOUSE_MODE_NONE 0
#define MOUSE_MODE_CREATING 1
#define MOUSE_MODE_MOVING 2
#define MOUSE_MODE_DEFORM 3


bool CheckCreat(std::vector<ControlObject*>& objects, POINT _left, POINT _right)
{
    _right.x += _left.x;
    _right.y += _left.y;

    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->CheckCrossing(_left, _right))
        {
            return false;
        }
    }
    return true;
}


bool CheckWalls(POINT _left, POINT _right, POINT size)
{
    _right.x += _left.x;
    _right.y += _left.y;
    return (_left.x >= 0 && _right.x <= size.x && _left.y >= 0 && _right.y <= size.y);
}