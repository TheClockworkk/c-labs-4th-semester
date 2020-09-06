#pragma once

#include "resource.h"
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <vector>
#define EPS 5


class ControlObject
{
protected:
	HWND hWnd;
	int id;
private:

	bool onSegment(POINT p, POINT q, POINT r)
	{
		if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
			q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
			return true;
		return false;
	}

	int orientation(POINT p, POINT q, POINT r)
	{
		int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

		if (val == 0) return 0;
		return (val > 0) ? 1 : 2;
	}


	bool doIntersect(POINT p1, POINT q1, POINT p2, POINT q2)
	{
		int o1 = orientation(p1, q1, p2);
		int o2 = orientation(p1, q1, q2);
		int o3 = orientation(p2, q2, p1);
		int o4 = orientation(p2, q2, q1);

		if (o1 != o2 && o3 != o4)
			return true;

		if (o1 == 0 && onSegment(p1, p2, q1)) return true;

		if (o2 == 0 && onSegment(p1, q2, q1)) return true;

		if (o3 == 0 && onSegment(p2, p1, q2)) return true;

		if (o4 == 0 && onSegment(p2, q1, q2)) return true;

		return false;
	}

public:
	POINT left, right;
	POINT size;
	ControlObject() : hWnd(NULL), id(0), left{ 0,0 }, right{ 0,0 }, size{ 0,0 }{};

	bool CheckCrossing(POINT _left, POINT _right)
	{
		int l = max(left.x, _left.x);
		int r = min(right.x, _right.x);
		int t = max(left.y, _left.y);
		int b = min(right.y, _right.y);
		int height = b - t;
		int width = r - l;
		return height >= 0 && width >= 0;
	}


	bool isInside(POINT p)
	{
		std::vector <POINT> polygon;
		POINT tmp;
		polygon.push_back(left);
		tmp.x = right.x;
		tmp.y = left.y;
		polygon.push_back(tmp);
		polygon.push_back(right);
		tmp.x = left.x;
		tmp.y = right.y;
		polygon.push_back(tmp);

		POINT extreme = { 10000, p.y };

		int count = 0, i = 0;
		do
		{
			int next = (i + 1) % polygon.size();

			if (doIntersect(polygon[i], polygon[next], p, extreme))
			{
				if (orientation(polygon[i], p, polygon[next]) == 0)
					return onSegment(polygon[i], p, polygon[next]);

				count++;
			}
			i = next;
		} while (i != 0);

		return count & 1;
	}

	int CheckAngle(POINT point)
	{
		if ((point.x - left.x) * (point.x - left.x) + (point.y - left.y) * (point.y - left.y) <= EPS * EPS) return 1;
		if ((point.x - right.x) * (point.x - right.x) + (point.y - left.y) * (point.y - left.y) <= EPS * EPS) return 2;
		if ((point.x - right.x) * (point.x - right.x) + (point.y - right.y) * (point.y - right.y) <= EPS * EPS) return 3;
		if ((point.x - left.x) * (point.x - left.x) + (point.y - right.y) * (point.y - right.y) <= EPS * EPS) return 4;
		return 0;
	}


	bool Move(int x, int y)
	{
		left.x += x;
		left.y += y;
		right.x += x;
		right.y += y;
		MoveWindow(hWnd, left.x + x, left.y + y, size.x, size.y, true);
		return true;
	}

	void Deform(int x, int y, int angle)
	{

		switch (angle)
		{
		case 1:
		{
			left.x += x;
			left.y += y;
			size.x += -x;
			size.y += -y;
			break;
		}
		case 2:
		{
			right.x += x;
			left.y += y;
			size.x += x;
			size.y += -y;
			break;
		}
		case 3:
		{
			right.x += x;
			right.y += y;
			size.x += x;
			size.y += y;
			break;
		}
		case 4:
		{
			left.x += x;
			right.y += y;
			size.x += -x;
			size.y += y;
			break;
		}
		default: break;
		}
		MoveWindow(hWnd, left.x, left.y, size.x, size.y, true);
	}
};


class ControlButton : public ControlObject
{
public:
	ControlButton() :ControlObject() {};
	ControlButton(HWND hWndParent, int x, int y, int width, int height, int _id)
	{
		id = _id;
		std::wstring name = L"Кнопка ";
		name += std::to_wstring(_id);
		hWnd = CreateWindow(L"BUTTON", name.c_str(), WS_CHILD | WS_VISIBLE | WS_DISABLED, x, y, width, height, hWndParent, NULL, GetModuleHandle(NULL), NULL);
		left.x = x;
		left.y = y;
		right.x = x + width;
		right.y = y + height;
		size.x = width;
		size.y = height;
	}
};


class ControlEdit : public ControlObject
{
public:
	ControlEdit() :ControlObject() {};
	ControlEdit(HWND hWndParent, int x, int y, int width, int height, int _id)
	{
		id = _id;
		std::wstring name = L"Ввод ";
		name += std::to_wstring(_id);
		hWnd = CreateWindow(L"EDIT", name.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | WS_DISABLED, x, y, width, height, hWndParent, NULL, GetModuleHandle(NULL), NULL);
		left.x = x;
		left.y = y;
		right.x = x + width;
		right.y = y + height;
		size.x = width;
		size.y = height;
	}
};

class ControlLabel : public ControlObject
{
public:
	ControlLabel() : ControlObject() {};
	ControlLabel(HWND hWndParent, int x, int y, int width, int height, int _id)
	{
		id = _id;
		std::wstring name = L"Надпись ";
		name += std::to_wstring(_id);
		hWnd = CreateWindow(L"STATIC", name.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED, x, y, width, height, hWndParent, NULL, GetModuleHandle(NULL), NULL);
		left.x = x;
		left.y = y;
		right.x = x + width;
		right.y = y + height;
		size.x = width;
		size.y = height;
	}
};

class ControlComboBox : public ControlObject
{
public:
	ControlComboBox() :ControlObject() {};
	ControlComboBox(HWND hWndParent, int x, int y, int width, int height, int _id)
	{
		id = _id;
		hWnd = CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED, x, y, width, height, hWndParent, NULL, GetModuleHandle(NULL), NULL);
		left.x = x;
		left.y = y;
		right.x = x + width;
		right.y = y + height;
		size.x = width;
		size.y = height;
	}
};

class ControlSpinButton : public ControlObject
{
public:
	ControlSpinButton() :ControlObject() {};
	ControlSpinButton(HWND hWndParent, int x, int y, int width, int height, int _id)
	{
		id = _id;
		hWnd = CreateWindow(L"SCROLLBAR", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED, x, y, width, height, hWndParent, NULL, GetModuleHandle(NULL), NULL);
		left.x = x;
		left.y = y;
		right.x = x + width;
		right.y = y + height;
		size.x = width;
		size.y = height;
	}
};