#include "App.h"
#include <cstdio> //IO includes NULL
#include <cstdlib> //includes srand and rand
#include <ctime> //time used for seed
#include <vector>

using namespace std;

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h)
{
    // Initialize state variables
    mx = 0.0;
    my = 0.0;

    /* POPULATING GAME SQUARES */

    Rect * rectangle1 = new Rect; //default rectangle is width and height 0.6
    rectangle1 -> setX(-1.0);
    rectangle1 -> setY(0.75);
    gameSquares.push_back(rectangle1); //left top

    Rect * rectangle2 = new Rect;
    rectangle2 -> setX(-1.0);
    rectangle2 -> setY(0.15);
    gameSquares.push_back(rectangle2); //left middle

    Rect * rectangle3 = new Rect;
    rectangle3 -> setX(-1.0);
    rectangle3 -> setY(-0.45); //left bottom
    gameSquares.push_back(rectangle3);

    Rect * rectangle4 = new Rect;
    rectangle4 -> setX(-0.3); //only using getHeight of the 0th square because its supposed to be a perfect square anyways and they're all supposed to be the same
    rectangle4 -> setY(0.75);
    gameSquares.push_back(rectangle4); //center top

    Rect * rectangle5 = new Rect;
    rectangle5 -> setX(-0.3);
    rectangle5 -> setY(0.15);
    gameSquares.push_back(rectangle5); //center middle

    Rect * rectangle6 = new Rect;
    rectangle6 -> setX(-0.3);
    rectangle6 -> setY(-0.45);
    gameSquares.push_back(rectangle6); //center bottom

    Rect * rectangle7 = new Rect;
    rectangle7 -> setX(0.4);
    rectangle7 -> setY(0.75);
    gameSquares.push_back(rectangle7); //right top

    Rect * rectangle8 = new Rect;
    rectangle8 -> setX(0.4);
    rectangle8 -> setY(0.15);
    gameSquares.push_back(rectangle8); //right middle

    Rect * rectangle9 = new Rect;
    rectangle9 -> setX(0.4);
    rectangle9 -> setY(-0.45);
    gameSquares.push_back(rectangle9); //right bottom

    /* POPULATING MENU SQUARES */

    Rect * one_player = new Rect(-1.0, 1.0, 2.0, 1.0, 1.0, 0.0, 0.0);
    menuScreenSquares.push_back(one_player);
    Rect * two_player = new Rect(0.0, 1.0, 2.0, 1.0, 0.0, 0.0, 1.0);
    menuScreenSquares.push_back(two_player);

    /* EVERYTHING ELSE */

    srand(time(NULL));

    if (int(rand() % 2) == 0) { currently_p1s_turn = true; }
    else { currently_p1s_turn = false; }
}

void App::resetGame(vector <Rect*> &gameSquares) //self-explanatory
{
	for (int i = 0; i < gameSquares.size(); i++)
	{
		gameSquares[i]->switchXTaken(false);
		gameSquares[i]->switchOTaken(false);
		gameSquares[i]->switchIsTaken(false);
	} //don't need to reconstruct the rectangles, the information is already there
	isSinglePlayer = false;
	playChoiceMade = false;
	if (int(rand() % 2) == 0) { currently_p1s_turn = true; }
	else { currently_p1s_turn = false; }
	counter = 0;

	redraw();
}

/* USED FOR DRAWING PURPOSES */

void drawDividerLines(float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(-0.38,0.75);
    glVertex2f(-0.38,-1.0);
    glVertex2f(-0.3,-1.0);
    glVertex2f(-0.3,0.75);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(0.32,0.75);
    glVertex2f(0.32,-1.0);
    glVertex2f(0.4,-1.0);
    glVertex2f(0.4,0.75);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0,0.2);
    glVertex2f(1.0,0.2);
    glVertex2f(1.0,0.15);
    glVertex2f(-1.0,0.15);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0,-0.4);
    glVertex2f(1.0,-0.4);
    glVertex2f(1.0,-0.45);
    glVertex2f(-1.0,-0.45);
    glEnd();
}

void drawTopBar(float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, 0.75);
    glVertex2f(-1.0, 0.75);
    glEnd();
}

void draw1P(float r, float g, float b, float x, float y, float width, float height)
{
   glColor3f(r,g,b);
   glBegin(GL_POLYGON);
   glVertex2f(x, y);
   glVertex2f(x, y - height);
   glVertex2f(x+width, y - height);
   glVertex2f(x+width, y);
   glEnd();
}

void draw2P(float r, float g, float b, float x, float y, float width, float height)
{
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_POLYGON);
   glVertex2f(x, y - (height/5));
   glVertex2f(x, y - (2*(height/5)));
   glVertex2f(x+(width/2), y - (2*(height/5)));
   glVertex2f(x+(width/2), y - (height/5));
   glEnd(); //inner block 1
   
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_POLYGON);
   glVertex2f(x+(width/2), y - (3*(height/5)));
   glVertex2f(x+(width/2), y - (4*(height/5)));
   glVertex2f(x+width, y - (4*(height/5)));
   glVertex2f(x+width, y - (3*(height/5)));
   glEnd(); //inner block 2

   glColor3f(r,g,b);
   glBegin(GL_POLYGON);
   glVertex2f(x, y); //0.25, 0.75
   glVertex2f(x, y - height);
   glVertex2f(x+width, y - height); //height 1
   glVertex2f(x+width, y); //width 0.5
   glEnd();  //block
}

void drawX(Rect * whereToDraw, float r, float g, float b) // works
{
	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex2f(whereToDraw->getX()+0.1, whereToDraw->getY()-0.1);
	glVertex2f(whereToDraw->getX()+whereToDraw->getWidth()-0.1, whereToDraw->getY()-whereToDraw->getHeight()+0.1);
	glEnd();

	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex2f(whereToDraw->getX()+whereToDraw->getWidth()-0.1, whereToDraw->getY()-0.1);
	glVertex2f(whereToDraw->getX()+0.1, whereToDraw->getY()-whereToDraw->getHeight()+0.1);
	glEnd();
}

void drawO(Rect * whereToDraw, float r, float g, float b, float radius = 0.2)
{
	Circle * drawnCircle = new Circle (whereToDraw->getCenterPointX(), whereToDraw->getCenterPointY(), radius, r, g, b);
	vector <Vec*> circlePoints = drawnCircle->getPoints();	
	for (int i = 0; i < circlePoints.size(); i++)
	{
		glColor3f(r, g, b);
		glBegin(GL_POINTS);
		glVertex2f(circlePoints[i]->getX(), circlePoints[i]->getY());
		glEnd();
	}
	delete drawnCircle;
}

void drawingSomeRectangles(vector <Rect*> thing)
{
    for (int i = 0; i < thing.size(); i++)
    {
	if (thing[i]->getIsTaken())
	{
		if (thing[i]->getXTaken()) { drawX(thing[i], 1.0, 0.0, 0.0); }
		else { drawO(thing[i], 0.0, 0.0, 1.0); }
	}

	glColor3f(thing[i]->getR(), thing[i]->getG(), thing[i]->getB());
    	// Draw some points
    	glBegin(GL_POLYGON);

    	glVertex2f(thing[i]->getX(), thing[i]->getY());
    	glVertex2f(thing[i]->getX()+thing[i]->getWidth(), thing[i]->getY());
    	glVertex2f(thing[i]->getX()+thing[i]->getWidth(), thing[i]->getY()-thing[i]->getHeight());
    	glVertex2f(thing[i]->getX(), thing[i]->getY()-thing[i]->getHeight());

    	glEnd();
    }
}

/* USED FOR CHECKING WIN */

/* VERTICAL POSSIBLE WINS: 0,1,2 | 3,4,5 | 6,7,8 */
bool xWinCheckVert(vector <Rect*> gameSquares)
{
	bool value = false;

	for (int i = 0; i <= 6; i+=3)
	{
		if (!value)
		{
			for (int j = i; j <= i+2; j++)
			{
				if (!gameSquares[j]->getXTaken()) { break; } //if there isn't an X, move to next row
				if (j == i+2) { value = true; } //prior to completing last loop, this becomes true
			}
		}
	}

	return value;
			
}
bool oWinCheckVert(vector <Rect*> gameSquares)
{
	bool value = false;

	for (int i = 0; i <= 6; i+=3)
	{
		if (!value)
		{
			for (int j = i; j <= i+2; j++)
			{
				if (!gameSquares[j]->getOTaken()) { break; } //if there isn't an X, move to next row
				if (j == i+2) { value = true; } //prior to completing last loop, this becomes true
			}
		}
	}

	return value;
			
}

/* HORIZONTAL POSSIBLE WINS: 0,3,6 | 1,4,7 | 2,5,8 */
bool xWinCheckHoriz(vector <Rect*> gameSquares)
{
	bool value = false;

	for (int i = 0; i < 3; i++)
	{
		if (!value)
		{
			for (int j = i; j <= i+6; j+=3)
			{
				if (!gameSquares[j]->getXTaken()) { break; } //if there isn't an X, move to next row
				if (j == i+6) { value = true; } //prior to completing last loop, this becomes true
			}
		}
	}

	return value;
}
bool oWinCheckHoriz(vector <Rect*> gameSquares)
{
	bool value = false;

	for (int i = 0; i < 3; i++)
	{
		if (!value)
		{
			for (int j = i; j <= i+6; j+=3)
			{
				if (!gameSquares[j]->getOTaken()) { break; } //if there isn't an X, move to next row
				if (j == i+6) { value = true; } //prior to completing last loop, this becomes true
			}
		}
	}

	return value;
}

/* DIAGONAL POSSIBLE WINS: 0,4,8 | 2,4,6 */
bool xWinCheckDiag(vector <Rect*> gameSquares)
{
	bool value = false;
	int increHelper = 1;

	for (int i = 0; i <= 2; i+=2)
	{
		if (!value)
		{
			for (int j = i; j <= 8-i; j+=(4/increHelper))
			{
				if(!gameSquares[j]->getXTaken()) { break; }
				if (j == (8-i)) { value = true; }
			}
			increHelper++;
		}
	}

	return value;
}
bool oWinCheckDiag(vector <Rect*> gameSquares)
{
	bool value = false;
	int increHelper = 1;

	for (int i = 0; i <= 2; i+=2)
	{
		if (!value)
		{
			for (int j = i; j <= 8-i; j+=(4/increHelper))
			{
				if(!gameSquares[j]->getOTaken()) { break; }
				if (j == (8-i)) { value = true; }
			}
			increHelper++;
		}
	}

	return value;
}

bool xWinCheck(vector <Rect*> gameSquares)
{
	return (xWinCheckHoriz(gameSquares) || xWinCheckVert(gameSquares) || xWinCheckDiag(gameSquares));
}
bool oWinCheck(vector <Rect*> gameSquares)
{
	return (oWinCheckHoriz(gameSquares) || oWinCheckVert(gameSquares) || oWinCheckDiag(gameSquares));
}

/* USED FOR DEBUGGING */
void debuggerXOLocation(vector <Rect*> gameSquares)
{
    cout << "X is located in: " << endl;
    for (int i = 0; i < gameSquares.size(); i++)
    {
	if (gameSquares[i]->getIsTaken() && gameSquares[i]->getXTaken())
	{
		cout << i << ", ";
	}
    }
    cout << endl << "O is located in: " << endl;
    for (int i = 0; i < gameSquares.size(); i++)
    {
	if (gameSquares[i]->getIsTaken() && gameSquares[i]->getOTaken())
	{
		cout << i << ", ";
	}
    }
    cout << endl << "------" << endl;
}

/* MAIN THINGS */

void App::draw() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (!playChoiceMade)
    {
	    draw1P(1.0, 1.0, 1.0, -0.65, 0.75, 0.2, 1.5);
	    draw2P(1.0, 1.0, 1.0, 0.25, 0.75, 0.5, 1.5);
	    drawingSomeRectangles(menuScreenSquares);
    }

    else if ((!xWinCheck(gameSquares) && !oWinCheck(gameSquares)) && counter < 9) //if they haven't won
    {
	    if (currently_p1s_turn) 
	    {	
		draw1P(1.0, 1.0, 1.0, -0.9, 0.95, 0.05, 0.15);
		drawTopBar(1.0, 0.0, 0.0); 
	    }
	    else
	    {
		draw2P(1.0, 1.0, 1.0, -0.95, 0.95, 0.2, 0.15); 
		drawTopBar(0.0, 0.0, 1.0); 
	    }
	    drawDividerLines(1.0, 1.0, 1.0);
	    drawingSomeRectangles(gameSquares);
	    debuggerXOLocation(gameSquares); //outputs locations of X and Os
    }
    else if (xWinCheck(gameSquares)) //if X won
    {
	    cout << "X IS WINRAR" << endl;
	    
	    Rect * fullScreen = new Rect (-1.0, 1.0, 2.0, 2.0, 1.0, 0.0, 0.0);

	    drawX(fullScreen, 1.0, 1.0, 1.0);

	    glColor3f(fullScreen->getR(), fullScreen->getG(), fullScreen->getB());
    	    // Draw some points
    	    glBegin(GL_POLYGON);

    	    glVertex2f(fullScreen->getX(), fullScreen->getY());
    	    glVertex2f(fullScreen->getX()+fullScreen->getWidth(), fullScreen->getY());
    	    glVertex2f(fullScreen->getX()+fullScreen->getWidth(), fullScreen->getY()-fullScreen->getHeight());
    	    glVertex2f(fullScreen->getX(), fullScreen->getY()-fullScreen->getHeight());

    	    glEnd();

	    delete fullScreen;
    }
    else if (oWinCheck(gameSquares)) //if O won
    {
	    cout << "O IS WINRAR" << endl;

	    Rect * fullScreen = new Rect (-1.0, 1.0, 2.0, 2.0, 0.0, 0.0, 1.0);
	    drawO(fullScreen, 1.0, 1.0, 1.0, 0.95);

	    glColor3f(fullScreen->getR(), fullScreen->getG(), fullScreen->getB());
    	    // Draw some points
    	    glBegin(GL_POLYGON);

    	    glVertex2f(fullScreen->getX(), fullScreen->getY());
    	    glVertex2f(fullScreen->getX()+fullScreen->getWidth(), fullScreen->getY());
    	    glVertex2f(fullScreen->getX()+fullScreen->getWidth(), fullScreen->getY()-fullScreen->getHeight());
    	    glVertex2f(fullScreen->getX(), fullScreen->getY()-fullScreen->getHeight());

    	    glEnd();

	    delete fullScreen;
    }
    else //neither have won and all spaces are filled based on counter
    {
	   cout << "CAT'S GAME" << endl;

	   Rect * fullScreen = new Rect (-1.0, 1.0, 2.0, 2.0, 1.0, 0.0, 1.0);
	   drawO(fullScreen, 1.0, 1.0, 1.0, 0.95);
	   drawX(fullScreen, 1.0, 1.0, 1.0);
	   
	   glColor3f(fullScreen->getR(), fullScreen->getG(), fullScreen->getB());
    	   // Draw some points
    	   glBegin(GL_POLYGON);

    	   glVertex2f(fullScreen->getX(), fullScreen->getY());
    	   glVertex2f(fullScreen->getX()+fullScreen->getWidth(), fullScreen->getY());
    	   glVertex2f(fullScreen->getX()+fullScreen->getWidth(), fullScreen->getY()-fullScreen->getHeight());
    	   glVertex2f(fullScreen->getX(), fullScreen->getY()-fullScreen->getHeight());

    	   glEnd();

	   delete fullScreen;
    }
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y)
{
    // Update app state
    mx = x;
    my = y;

    if (!playChoiceMade)
    {
	for (int i = 0; i < menuScreenSquares.size(); i++)
        {
		if (menuScreenSquares[i]->contains(mx, my) && i == 0)
		{
			playChoiceMade = true;
			isSinglePlayer = true;

			if (!currently_p1s_turn) //If "AI" starts the game
			{
				int randomGenerated = rand() % 9; //pick a number between 0 to 9
				while (gameSquares[randomGenerated]->getIsTaken())
					randomGenerated = rand() % 9; //pick another number

				gameSquares[randomGenerated]->switchIsTaken(true);
				gameSquares[randomGenerated]->switchOTaken(true);
				counter++;
				currently_p1s_turn = true;
			}

			break;
		}
		else
		{
			playChoiceMade = true;
			isSinglePlayer = false;
			break;
		}
	}
 	cout << "Starting a new ";
	isSinglePlayer ? cout << "single player game." << endl : cout << "multi player game." << endl;
    }
	
    else if (isSinglePlayer && (!xWinCheck(gameSquares) && !oWinCheck(gameSquares)) && counter < 9) 
    {
	    if (currently_p1s_turn) //used for if p1 went first
	    {
	    	for (int i = 0; i < gameSquares.size(); i++)
	    	{
			if (gameSquares[i]->contains(mx, my) && !gameSquares[i]->getIsTaken()) //if it's within the square and is not taken
			{
		 		gameSquares[i]->switchIsTaken(true);
				if (currently_p1s_turn)
				{
					gameSquares[i]->switchXTaken(true);
					currently_p1s_turn = false; //no longer p1's turn afterwards
					counter++;	

					/* THE "AI"'s turn (lol rng) */
					if (counter < 9)
					{
				        	int randomGenerated = rand() % 9; //pick a number between 0 to 9
						while (gameSquares[randomGenerated]->getIsTaken())
							randomGenerated = rand() % 9; //pick another number

						gameSquares[randomGenerated]->switchIsTaken(true);
						gameSquares[randomGenerated]->switchOTaken(true);
						counter++;
						currently_p1s_turn = true;
					}	
		
					break;
				}
			}
		    }
	    }
    }
	
    else if (!isSinglePlayer && (!xWinCheck(gameSquares) && !oWinCheck(gameSquares)) && counter < 9) 
    {
	    for (int i = 0; i < gameSquares.size(); i++)
	    {
		if (gameSquares[i]->contains(mx, my) && !gameSquares[i]->getIsTaken()) //if it's within the square and is not taken
		{
	 		gameSquares[i]->switchIsTaken(true);
			if (currently_p1s_turn)
			{
				gameSquares[i]->switchXTaken(true);
				currently_p1s_turn = false; //no longer p1's turn afterwards
				counter++;				
				break;
			}
			else
			{
				gameSquares[i]->switchOTaken(true);
				currently_p1s_turn = true; //becomes p1's turn afterwards
				counter++;
				break;
			}
		}
	    }
    }

    else if (xWinCheck(gameSquares) || oWinCheck(gameSquares) || counter == 9) //X, O won or nobody won
    {
	resetGame(gameSquares);
    }

    else { /* do nothing, just hate having else if hanging */ }

    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y)
{
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) 
{
    if (key == 27)
    {
        // Exit the app when Esc key is pressed
        exit(0);
    }
}
