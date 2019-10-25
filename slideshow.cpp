//--------------------------------------------------------------------
//
//  Laboratory 5, Programming Exercise 1                 slideshow.cpp
//
//--------------------------------------------------------------------

// Displays a slide show.

// Uncomment the following line if running in windows
// #define WIN32

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#include "ListLinked.h"

//--------------------------------------------------------------------

// This is a very ugly way to wait for a specified amount of time.
// It is ugly because it runs the CPU the whole time, instead of
// just suspending the process for the required time period.
// However, it is also very portable.  This function should work on
// all platforms that support ANSI C++.  Feel free to replace this
// with something nicer (such as sleep or usleep) if you so choose.
void wait(int secs) 
{
    int start=clock();
	
    while (clock() < start + secs * CLOCKS_PER_SEC);
}

//--------------------------------------------------------------------

class Slide
	{
	public:
		static const int HEIGHT = 10,		// Slide dimensions
		WIDTH  = 36;
		
		void display () const;			// Display slide and pause
		
	private:
		
		char image [HEIGHT][WIDTH];  	   // Slide image
		int pause;				   // Seconds to pause after
		//  displaying slide
		
		friend istream& operator>> (istream& in, Slide& slide);
        friend ostream& operator<< (ostream& out, const Slide& slide);
	};

//--------------------------------------------------------------------

int main ()
{
    List<Slide> slideShow;    // Slide show
    Slide currSlide;                // Slide
    char filename[81];              // Name of slide show file
	
    // Read the slide show from the specified file.
	
    cout << endl << "Enter the name of the slide show file : ";
    cin >> filename;
	
    ifstream slideFile ( filename );
	
    if ( !slideFile )
    {
		cout << "Error opening file " << filename << endl;
    }
    else
    {
		// Read in the slides one-by-one.
		while ( slideFile >> currSlide )
		{
			// currSlide is the most recently read Slide
			/**** YOUR CODE HERE ****/
            slideShow.insert(currSlide);

			/****                ****/
		}
		
		// Close the file.
		slideFile.close();
		
		// Display the slide show slide-by-slide.
		/**** YOUR CODE HERE ****/
        slideShow.gotoBeginning();
        currSlide = slideShow.getCursor();
        currSlide.display();
        while(slideShow.gotoNext())
        {
            currSlide = slideShow.getCursor();
            currSlide.display();
        }

		/****                ****/		
    }
	
    return 0;
}

//--------------------------------------------------------------------
//

istream& operator>> (istream& inFile, Slide& slide)
// Read a slide from inFile.
{
    char skipCR;   // Used to skip newline marker
	
    inFile >> slide.pause;
    inFile.get(skipCR);
    for ( int j = 0 ; j < Slide::HEIGHT ; j++ )
    {
        inFile.getline(slide.image[j],Slide::WIDTH,'\n');
    }
	return inFile; 
}


//____________________________________________________

ostream& operator<< (ostream& out, const Slide& slide)
{	/**** YOUR CODE HERE ****/
    for(int height = 0; height < slide.HEIGHT; height++)
    {
        for(int width = 0; width < slide.WIDTH; width++)
        {
            out << slide.image[height][width];
        }
        out << endl;
    }
    return out;
}

//--------------------------------------------------------------------

void Slide:: display () const
// Display the slide image, then wait for 'pause' seconds.
{
	
    /**** YOUR CODE HERE ****/
    cout << *this;
    wait(pause);
}
