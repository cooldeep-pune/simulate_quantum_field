#include <iostream>
#include <cstdio>
#include "SingleFieldTypeUniverse.h"
using namespace std;

SingleFieldTypeUniverse* SingleFieldTypeUniverse::instance_ = nullptr;
std::mutex SingleFieldTypeUniverse::m_singletonMutex;
std::mutex SingleFieldTypeUniverse::glock;
UField SingleFieldTypeUniverse::m_space[SPACE][SPACE][SPACE];


void SingleFieldTypeUniverse::InitializeUniverse(){
	cout<<"Initializing SingleFieldTypeUniverse"<<endl;
	cout<<"size of space: "<<sizeof(m_space)<<endl;
		for(int z=0;z<SPACE;z++) 
		for(int y=0;y<SPACE;y++) 
			for(int x=0;x<SPACE;x++) {
				m_space[z][y][x].energylevel= 0;
				m_space[z][y][x].time=0;
				m_space[z][y][x].spin=0;
			}
}

void SingleFieldTypeUniverse::SimulateUniverse(){
	cout<<"Simulating SingleFieldTypeUniverse...."<<endl;
	
 	 for (int i =0;i<64;i++){
	  
		srand((unsigned) time(NULL));
		int random = rand() % 17;

		std::vector<std::thread> workers;
		
		int threads = 8;
		int energyoffset = 2;

		for(int i =0;i<threads;i++) {
			int cnt = i;
			workers.push_back(std::thread(InAction,energyoffset));
			//workers.push_back(std::thread(LayeredAction,random));
		}
		if(random==0)
			GodThread();
		//Display();
		for(int i =0;i<threads;i++) {
			workers[i].join();
		
		}
		workers.clear();
	}
	SaveToFile();
}
 void SingleFieldTypeUniverse::SaveToFile(){

	std::string name = std::tmpnam(nullptr);
	name = "c:\\temp" + name + "bin";
    std::cout << "temporary file name: " << name << '\n';
   ofstream myFile (name, ios::out | ios::binary);
   	for (int i =0;i<SPACE;i++)
		for (int j =0; j<SPACE;j++)
			for (int k =0; k<SPACE;k++)
				myFile.write ((char*)&m_space[i][j][k].energylevel,sizeof(short int));
   
   myFile.close();
	
}

void SingleFieldTypeUniverse::GodThread()
{
	bool breakme = false;
	srand((unsigned) time(NULL));
	// Get a random number
	//double slope = 2.0f/ 65535.0f;
	int x_random = rand() % SPACE; // x pixel position of center
	int y_random = rand() % SPACE; // y pixel position of center
	int z_random = rand() % SPACE; // y pixel position of center
	int wavelength = 4;
	float trainwidth = 1.4F;
	const double pi = 3.14159265358979323846;
	
	for(int z = z_random;z<SPACE;z++) {
		for(int y=y_random;y<SPACE;y++) {
			for(int x=x_random;x<SPACE;x++) {
				if(z<SPACE-4){
					if((m_space[z][y][x].energylevel>0) && (m_space[z+2][y][x].energylevel>0)){
						x_random = x;
						x_random = y;
						z_random = z;
						breakme = true;
						break;
					}
				}
			}
			if(breakme==true){
				break;
			}
		}
		if(breakme==true){
			break;
		}
	}
		
	if(breakme==true){ 		 
		int depth = z_random + 8;
		if(depth > SPACE)
			depth = SPACE;
			
		for(int z = z_random;z<depth;z++)
			for(int y=0;y<SPACE;y++)
				for(int x=0;x<SPACE;x++) {			
					double dx = x- x_random ; // or int, if the center coords are ints
					double dy = y- y_random ;
					double r = (sqrt(dx*dx+dy*dy)-RADIUS)/wavelength ;
					double k = r - (1-SUPERPHASE)*RADIUS/wavelength ;
					double a = 1 / (1.0 + (r/trainwidth)*(r/trainwidth));
					int value = (int)floor(a * 1.0f/(sin(k*2*pi)));
					if(value < -1)
					{
						m_space[z][y][x].energylevel =  -10;
						
					} else if(value == 0)
					{
						m_space[z][y][x].energylevel = 0;
					} else
					{
						m_space[z][y][x].energylevel =  10;
					}
							
				}
	}
}
	

void SingleFieldTypeUniverse::InAction(int energyboost){
	//std::lock_guard<std::mutex> lockGuard(glock);
	const double pi = 3.14159265358979323846;
	srand((unsigned) time(NULL));
	// Get a random number
	//double slope = 2.0f/ 65535.0f;
	int x_random = rand() % SPACE; // x pixel position of center
	int y_random = rand() % SPACE; // y pixel position of center
	int z_random = rand() % SPACE; // y pixel position of center
	int wavelength = WAVELENGTH;
	float trainwidth = TRAINWIDTH;
	if(energyboost == 2) {
		wavelength = 8;
		trainwidth = 2.4f;
	}
	
	int depth = z_random + 4;
	if(depth > SPACE)
		depth = SPACE;
		
	for(int z = z_random;z<depth;z++)
		for(int y=0;y<SPACE;y++) 
			for(int y=0;y<SPACE;y++) 
				for(int x=0;x<SPACE;x++) {
					double dx = x- x_random ; // or int, if the center coords are ints
					double dy = y- y_random ;
					if((x > 64) && (y > 64)) {
						wavelength = 16;
					}
					double r = (sqrt(dx*dx+dy*dy)-RADIUS)/wavelength ;
					double k = r - (1-SUPERPHASE)*RADIUS/wavelength ;
					double a = 1 / (1.0 + (r/trainwidth)*(r/trainwidth));
					int value = (int)floor(a * sin(k*2*pi));
					if(value < -1)
					{
						m_space[z][y][x].energylevel =  -1;
					} else if(value == -1)
					{
						m_space[z][y][x].energylevel = 0;
					} else
					{
						m_space[z][y][x].energylevel =  1;
					}
							
				}
}

/*void  SingleFieldTypeUniverse::rotate_sphere(int x0,int y0,int z0,int r)
    {
    int x,y,z,xa,ya,za,xb,yb,zb,xr,yr,zr,xx,yy,zz,rr=r*r;
    // bounding box
    xa=x0-r; if (xa<0) xa=0; xb=x0+r; if (xb>n) xb=n;
    ya=y0-r; if (ya<0) ya=0; yb=y0+r; if (yb>n) yb=n;
    za=z0-r; if (za<0) za=0; zb=z0+r; if (zb>n) zb=n;
    // project xy plane
    for (x=xa,xr=x-x0,xx=xr*xr;x<xb;x++,xr++,xx=xr*xr)
     for (y=ya,yr=y-y0,yy=yr*yr;y<yb;y++,yr++,yy=yr*yr)
        {
        zz=rr-xx-yy; if (zz<0) continue; zr=sqrt(zz);
        z=z0-zr; if ((z>0)&&(z<n)) m_space[x][y][z]=col;
        z=z0+zr; if ((z>0)&&(z<n)) m_space[x][y][z]=col;
        }
    // project xz plane
    for (x=xa,xr=x-x0,xx=xr*xr;x<xb;x++,xr++,xx=xr*xr)
     for (z=za,zr=z-z0,zz=zr*zr;z<zb;z++,zr++,zz=zr*zr)
        {
        yy=rr-xx-zz; if (yy<0) continue; yr=sqrt(yy);
        y=y0-yr; if ((y>0)&&(y<n)) m_space[x][y][z]=col;
        y=y0+yr; if ((y>0)&&(y<n)) m_space[x][y][z]=col;
        }
    // project yz plane
    for (y=ya,yr=y-y0,yy=yr*yr;y<yb;y++,yr++,yy=yr*yr)
     for (z=za,zr=z-z0,zz=zr*zr;z<zb;z++,zr++,zz=zr*zr)
        {
        xx=rr-zz-yy; if (xx<0) continue; xr=sqrt(xx);
        x=x0-xr; if ((x>0)&&(x<n)) map[x][y][z]=col;
        x=x0+xr; if ((x>0)&&(x<n)) map[x][y][z]=col;
        }
}*/
void SingleFieldTypeUniverse::LayeredAction(int energyboost){

	srand((unsigned) time(NULL));
	// Get a random number
	int x_random = rand() % SPACE; // x pixel position of center
	int y_random = rand() % SPACE; // y pixel position of center
	int z_random = rand() % SPACE; // y pixel position of center
	
	int depth = z_random + 4;
	if(depth > SPACE)
		depth = SPACE;
		
	int pixel = rand() % 256;
		
	for(int z=z_random;z<depth;z++) {
		for(int y=y_random;y<SPACE;y++) 
			for(int x=x_random;x<SPACE;x++) {
				m_space[z][y][x].energylevel= pixel;
			} 
	}

}
void SingleFieldTypeUniverse::ClearScreen()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

void SingleFieldTypeUniverse::Display(){
	for (int i =0;i<SPACE;i++) {
		ClearScreen();
		for (int j =0; j<SPACE;j++) {
			for (int k =0; k<SPACE;k++) {
				if(m_space[i][j][k].energylevel>0)
					//std::cout<<"\033[1;31mO\033[0m";
					std::cout<<1;
				else
					//std::cout<<"\033[1;30mO\033[0m";
					std::cout<<0;
			}
			cout<<endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
}