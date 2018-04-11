#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "Vec.h"

#include <vector>
#include <cmath>

using namespace std;

class Rect
{
  private:
    float x;
    float y;
    float height;
    float width;

    float red;
    float green;
    float blue;

    bool isTaken;
    bool xTaken;
    bool oTaken;

    float center_point_x; //used for getting center point for circle drawing
    float center_point_y;

  public:
    Rect()
    {
	this->x = 0.0;
	this->y = 0.0;
	this->height = 0.55;
	this->width = 0.62;

        this->red = 0.0;
	this->green = 0.0;
	this->blue = 0.0;

	this->xTaken = false;
	this->oTaken = false;
	this->isTaken = false;

	this->center_point_x = this->x + ((this->width)/2);
        this->center_point_y = this->y - ((this->height)/2);
    }

    Rect(float x, float y, float height, float width, float r, float g, float b)
    {
        this->x = x;
        this->y = y;
        this->height = height;
        this->width = width;

	this->red = r;
	this->green = g;
	this->blue = b;

	this->xTaken = false;
	this->oTaken = false;
	this->isTaken = false;

	this->center_point_x = this->x + ((this->width)/2);
        this->center_point_y = this->y - ((this->height)/2);
    }

    void setX(float x) 
    { 
	this->x = x; 
	this->center_point_x = this->x + ((this->width)/2);
    }
    void setY(float y)
    { 
	this->y = y; 
        this->center_point_y = this->y - ((this->height)/2);
    }
    void setHeight(float height) 
    { 
	this->height = height; 
        this->center_point_y = this->y - ((this->height)/2);
    }
    void setWidth(float width)
    { 
	this->width = width; 
	this->center_point_x = this->x + ((this->width)/2);
    }

    void setR(float r) { this->red = r; }
    void setG(float g) { this->green = g; }
    void setB(float b) { this->blue = b; }

    void switchXTaken(bool value) { this->xTaken = value; } //switches it from true to false or vice versa
    void switchOTaken(bool value) { this->oTaken = value; }
    void switchIsTaken(bool value) { this->isTaken = value; }

    float getX() { return this->x; }
    float getY() { return this->y; }
    float getHeight() { return this->height; }
    float getWidth() { return this->width; }

    float getR() { return this->red; }
    float getG() { return this->green; }
    float getB() { return this->blue; }

    float getCenterPointX() { return this->center_point_x; }
    float getCenterPointY() { return this->center_point_y; }

    bool getIsTaken() { return this->isTaken; }
    bool getXTaken() { return this->xTaken; }
    bool getOTaken() { return this->oTaken; }

    bool contains(float x0, float y0)
    {
      return (x0 <= this->x+this->width && x0 >= this->x) && (y0 >= (this->y - this->height) && y0 <= this->y);
    }

    ~Rect() { }
};

class Circle
{
    private:
	vector <Vec*> points;
	const double incrementor = (2*M_PI)/1000; //sooper good looking circles
	float center_point_x;
	float center_point_y;
	float radius;
	//assume resolution is good shit

	float red;
	float green;
	float blue;

    public:
	Circle() //generate a white unit circle at origin
	{
		this->center_point_x = 0.0;
		this->center_point_y = 0.0; 
		this->radius = 1.0;

		this->red = 1.0;
		this->green = 1.0;
		this->blue = 1.0;

		// Clear the points vector to make sure it's empty before you start
		(this->points).clear();
		for (double angle = 0.0; angle < 2*M_PI; angle+=(this->incrementor))
		{
			float xx = this->center_point_x + this->radius * cos(angle);
			float yy = this->center_point_y + this->radius * sin(angle); 

			Vec * temp = new Vec;
			temp->setX(xx);
			temp->setY(yy);
			(this->points).push_back(temp); //generate points for circle
		}	
	} 
	Circle(float center_x, float center_y, float radius, float red, float green, float blue)
	{
		this->center_point_x = center_x;
		this->center_point_y = center_y; 
		this->radius = radius;

		this->red = red;
		this->green = green;
		this->blue = blue;

		// Clear the points vector to make sure it's empty before you start
		(this->points).clear();
		for (double angle = 0.0; angle < 2*M_PI; angle+=(this->incrementor))
		{
			float xx = this->center_point_x + this->radius * cos(angle);
			float yy = this->center_point_y + this->radius * sin(angle); 

			Vec * temp = new Vec;
			temp->setX(xx);
			temp->setY(yy);
			(this->points).push_back(temp); //generate points for circle
		}
	}

	void outerGenerateCircleData()
	{
	    // Clear the points vector to make sure it's empty before you start, sicne we are resetting points
	    (this->points).clear();
	    for (double angle = 0.0; angle < 2*M_PI; angle+=(this->incrementor))
	    {
		float xx = this->center_point_x + this->radius * cos(angle);
		float yy = this->center_point_y + this->radius * sin(angle); 

		Vec * temp = new Vec;
		temp->setX(xx);
		temp->setY(yy);
		(this->points).push_back(temp);
	    }
	}

	float getCenterX() { return this->center_point_x; }
	float getCenterY() { return this->center_point_y; }
	float getRadius() { return this->radius; }
	vector <Vec*> getPoints() { return this->points; }

	void setCenterX(float center_x)
	{
		this->center_point_x = center_x;
		outerGenerateCircleData();
	}

	void setCenterY(float center_y)
	{
		this->center_point_y = center_y;
		outerGenerateCircleData();
	}

	void setRadius(float radius)
	{
		this->radius = radius;
		outerGenerateCircleData(); //regenerate points with our new circle
	}

	~Circle() { }	
};

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;

    std::vector <Rect*> menuScreenSquares;
    std::vector <Rect*> gameSquares;

    bool currently_p1s_turn = false;
    bool isSinglePlayer = false;
    bool playChoiceMade = false;

    int counter = 0; //keeps track of moves done

public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    void resetGame(vector <Rect*> &gameSquares);
};

#endif
