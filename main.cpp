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
    vector<Barrier*> barriers;
public:
    Emulator(vector<Barrier*>&barriers)
    {
        this->barriers=barriers;
    }

    vector<int> foo(Point position, float widthNav, float heightNav)
    {
        vector<int> out;
        widthNav=widthNav/2;
        for(int i=0; i<barriers.size();i++)
        {
            Point leftTop(barriers[i]->x-barriers[i]->width/2.0, barriers[i]->y+barriers[i]->height/2.0);
            Point rightBottom(barriers[i]->x+barriers[i]->width/2.0,barriers[i]->y-barriers[i]->height/2.0);
            if(!(position.x-widthNav > rightBottom.x || position.x+widthNav < leftTop.x ||
                 position.y > rightBottom.y || position.y-heightNav > leftTop.y))
                out.push_back(i);
        }
        return out;
    }
    ~Emulator()
    {
        for(auto it= barriers.begin(); it!=barriers.end(); ++it)
            delete(*it);
    }
};

int main()
{
    vector<Barrier*> vecBar;
    vecBar.push_back(new Barrier(0,0,0,0));
    vecBar.push_back(new Barrier(10,0,0,0));
    vecBar.push_back(new Barrier(-10,0,0,0));
    vecBar.push_back(new Barrier(0,10,0,0));
    vecBar.push_back(new Barrier(0,-10,0,0));

    vecBar.push_back(new Barrier(10,10,0,0));
    vecBar.push_back(new Barrier(-10,-10,0,0));
    vecBar.push_back(new Barrier(-10,10,0,0));
    vecBar.push_back(new Barrier(10,-10,0,0));
    Emulator emu(vecBar);

    auto vec=emu.foo(Point(0,0),2,100);
    for(int i=0; i<vec.size();i++)
        cout<<vec[i];
    return 0;
}
