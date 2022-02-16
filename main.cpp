#include <iostream>
#include <vector>

using namespace std;

class Point
{

public:
    float x;
    float y;
    Point():x(0),y(0)
    {

    }
    Point(float x, float y):x(x),y(y)
    {

    }
    Point (const Point& o):x(o.x),y(o.y)
    {

    }
};

class Barrier:public Point
{
private:
public:
    float width;
    float height;
    Barrier():Point(),width(0),height(0)
    {

    }
    Barrier(float x, float y, float width, float height):Point(x,y),width(width), height(height)
    {

    }
    Barrier(Point position, float width, float height):Point(position), width(width), height(height)
    {

    }
    Barrier (const Barrier& o):Point(o.x,o.y),width(o.width),height(o.height)
    {

    }
};

class Emulator
{
private:
    vector<Barrier> barriers;
public:
    Emulator(vector<Barrier>&barriers)
    {
        this->barriers=barriers;
    }

    void foo(vector<Barrier>& out, float width, float height, Point position, float widthNav, float heightNav)
    {
        float widthMap=width/2;
        float heightMap=-height/2;
        widthNav=widthNav/2;
        for(int i=0; i<barriers.size();i++)
        {
            Point leftTop(barriers[i].x-barriers[i].width/2.0, barriers[i].y+barriers[i].height/2.0);
            Point rightBottom(barriers[i].x+barriers[i].width/2.0,barriers[i].y-barriers[i].height/2.0);
            if(!(position.x-widthNav > rightBottom.x || position.x+widthNav < leftTop.x ||
                 position.y > rightBottom.y || position.y-heightNav > leftTop.y))
                out.push_back(barriers[i]);
            //Проверка на принадлежность глобальной карте
            //if(!(-widthMap > rightBottom.x || widthMap < leftTop.x || -heightMap < rightBottom.y || heightMap > leftTop.y))
            //    out.push_back(barriers[i]);
        }
    }
};

int main()
{
    vector<Barrier> vecBar, vecBarOut;
    vecBar.push_back(Barrier(0,0,0,0));
    vecBar.push_back(Barrier(10,0,0,0));
    vecBar.push_back(Barrier(-10,0,0,0));
    vecBar.push_back(Barrier(0,10,0,0));
    vecBar.push_back(Barrier(0,-10,0,0));

    vecBar.push_back(Barrier(10,10,0,0));
    vecBar.push_back(Barrier(-10,-10,0,0));
    vecBar.push_back(Barrier(-10,10,0,0));
    vecBar.push_back(Barrier(10,-10,0,0));
    Emulator emu(vecBar);

    emu.foo(vecBarOut,1000,1000,Point(0,0),2,100);
    for(int i=0; i<vecBarOut.size();i++)
        cout<<vecBarOut[i].x<<'\t'<<vecBarOut[i].y<< endl;
    return 0;
}
