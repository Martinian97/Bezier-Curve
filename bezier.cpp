#include<simplecpp>
#include<fstream>

struct Points								//struct definition of points
{
  double x,y;								//to store the x and y co-ordinates
  Points() {}
};

Points divide(Points p,Points q,float t)				//function to divide the line segment between two points in ratio t:1-t
{
	Points n;
	n.x=t*p.x+(1-t)*(q.x);						//division of x co-ordinates 
	n.y=t*p.y+(1-t)*(q.y);						//division of y co-ordinates
  return n;								//return the new co-ordinates
}

Points bezier(vector<Points> p,float t)					//function to find the new points
{
	if(p.size()==1) return p[0];					//if vector contains only one point then return its co-ordinates
	vector<Points> q;
	size_t c=0;
	while(c<p.size()-1)						//until you reach the end	
	{
		q.push_back(divide(p[c],p[c+1],t));			//push back the new co-ordinates by call to function divide in a new vector 
		c++;
	}
  return bezier(q,t);							//call the same function with the vector of new co-ordinates
}

int main()
{
  initCanvas("BEZIER CURVE",1000,1000);					//canvas of 1000x1000						
  Points p;	
  vector<Points> data;				
  int num,a,b;
  float t=0,delta;

  ifstream in("data.txt");						//filename 'data' for input	
  in>>num;								//input the number of co-ordinates	
  while(num>0)
  { 
	in>>a>>b;							//input the co-ordinates
	num--;
	p.x=a;								//store the first co-ordinate input in struct attribute x
	p.y=b;								//store the second co-ordinate input in struct attribute y
	Circle c1(p.x,p.y,1);						//to mark a point at the co-ordinates
  	c1.imprint();
	data.push_back(p);						//push back the co-ordinates in 'data'
  }
  in>>delta; 								//input the value of Delta
  Points o,n;								//for old and new co-ordinates
  while(t<=1)
  {
	o=bezier(data,t);						//saves old co-ordinate
	n=bezier(data,t+delta);						//saves new co-ordinate 
	Line l(o.x,o.y,n.x,n.y);					//draw a line between the two points
	l.imprint();
	t=t+delta;							//increment t by delta
	if(t<0.505 and t>0.495)						//for t=0.5 condition
	{	
		cout<<n.x<<", "<<n.y<<endl;				//print the co-ordinates
	}
  }
 wait(2);
}
							
