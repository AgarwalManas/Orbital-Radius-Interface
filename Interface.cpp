// calculation of orbital radius by inputing zenith angle(in degree) and velocity at burnout(km/h) from 200km to 300km altitude range at 10km difference 
//
// Name: Manas Agarwal
// Student Number: 101007378 

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

bool isInt (double value) {
    double dummy;
    return bool(modf(value, &dummy) == 0);
}

double sqr(double value) { 
	return value * value; 
}
double calculateRadius2 (double C, double gama_radian, double d){
	
		double 	Rp2,				// orbital radius 2 (with negative sign in eqaution) in metres
				x,					// variable given to calculate some part of the numerator of equation
				y,					// variable given to calculate some part of the numerator of equation
				z;			 		// variable given to calcuate the denominator part of equation
				
				
	x = 4*(C-1)*(pow(sin(gama_radian),2));
	y = pow(C,2);
	z = 2*(1-C);
	
	Rp2 =  d*(-C - sqrt(y-x))/z;
	
	return Rp2;
}

double calculateRadius1 (double C, double gama_radian, double d){
	
	double 	Rp1, 					// orbital radius 1 (with positive sign in equation) in metres
			x,						// variable given to calculate some part of the numerator of equation
			y,						// variable given to calculate some part of the numerator of equation
			z; 						// variable given to calcuate the denominator part of equation
			
			
	x = 4*(C-1)*(pow(sin(gama_radian),2));
	y = pow(C,2);
	z = 2*(1-C);
	
	Rp1 = d*(-C + sqrt(y-x))/z;

	return Rp1;
}
double orbitParameter(double d, double v){
	
	double C; 						// intermediate result
	const double GM = 3.986005e14; 	// constant which is needed to caculate intermediate result
	
	C = (2*GM) / (d*pow(v,2));
	
	return C;
}

int main (void) {

    double 	gama,			// zenith angle at burnout (in degrees)
			v,				// velocity at burnout (in km/hr)
			d,				// orbital distance in km (distance from centre of earth to the orbit at burnout)
			altitude=0,		// altitude in km
			d_metre,		// orbital distance in metres (distance from centre of earth to the orbit at burnout)
			v_ms,			// velocity  at burnout (in m/s)
			C,				// intermediate result
			R1,				// orbital radius 1 (with positive sign in equation) in metres
			R2,				// orbital radius 2 (with positive sign in equation) in metres
			R1_km,			// orbital radius 1 (with positive sign in equation) in km
			R2_km,			// orbital radius 2 (with positive sign in equation) in km
			gama_radian,	// zenith angle at burnout (in radian)
			x=0,			// sum of all periapsis in 1 trial
			y=0,			// sum of all apoapsis in 1 trial
			ap_avg,			// average apoapsis in 1 trial
			pe_avg,			// average periapsis in 1 trial
			largest=0,		// largest Periapsis 
			n=0; 			// number of trials
    const double r = 6378.14;
    
    cout<< "Please enter the zenith angle (85.00-95.00 degrees)"<<
	" and burnout velocity (21600.00 to 29000.00 km/h) (0 0 to exit):  ";
    cin >> gama>>v;
    
    while (gama!= 0 || v !=0 ){
    	
    	
    	while (gama>=85 && gama <=95 && v>=21600 && v<=29000){
    		
    	
			gama_radian = gama * M_PI/180;		// converting zenith angle from degree to radian ( and MP1 is in built pi)
    		
    		cout <<setw(8)<<left<<"Altitude (km)"<<
			setw(18)<<right<<"Apoapsis (km)"<<
			setw(15)<<"Periapsis (km)"<<endl;
    		
    		for (altitude = 200; altitude<=300; altitude = altitude+10){
    	
			d = r + altitude; 									//distance from centre of earth to the orbit at burnout in (km) (that is radius of earth + altitude)
    	
				d_metre = d*1000; 								// distance from centre of earth to theorbit at burnout in (m)
    			v_ms = v/3.6;									// velocity at burnout (in m/sec) (3.6 is the converting factor between km/hr to m/sec)
    		
				
				C = orbitParameter (d_metre,v_ms);				// obtaining intermediate result from fuction "orbitParameter"
				R1 = calculateRadius1 (C,gama_radian,d_metre);	// obtaining Radius 1 from function "calculateRadius1"
				R2 = calculateRadius2 (C,gama_radian,d_metre); 	// obtaining Radius 1 from function "calculateRadius1"
				
				R1_km = R1/1000; 								//converting R1 to km
				R2_km = R2/1000; 								//converting R2 to km
				
				cout<<setw(8)<<fixed<<setprecision(0)<<right<<altitude<<
				setw(18)<<right<<fixed<<setprecision(2)<<R2_km<<
				setw(14)<<fixed<<setprecision(2)<<R1_km<<endl;
				
				
				x = x + R1_km; 									// sum of all periapsis in 1 trial
				y = y + R2_km; 									// sum of all apoapsis in 1 trial
				
				
				if (largest<=R1_km){ 							// largest Periapsis in 1 trial
					largest = R1_km;
				}
				
			ap_avg = y/11;	// average apoapsis  in 1 trial
			pe_avg = x/11;	// average periapsis in 1 trial
    			
    		}
			n = n + 1;		// total number of trials
			
			cout<<endl;
			
    		cout<< "Please enter the zenith angle (85.00-95.00 degrees)"<<
			" and burnout velocity (21600.00 to 29000.00 km/h) (0 0 to exit):  ";
    		cin >> gama>>v;
    		
    	}
    	
    		if(gama==0 && v==0){
    		break;
    	}
    	
    cout<<"Input values are invalid."<<endl;
	cout<<endl;
	
	cout<< "Please enter the zenith angle (85.00-95.00 degrees)"<<
	" and burnout velocity (21600.00 to 29000.00 km/h) (0 0 to exit):  ";
    cin >> gama>>v;	
    	
    }
    
    cout <<"Average apoasis radius is: "<<
	fixed<<setprecision(2)<<ap_avg/n<<" km"<<endl;
	
    cout << "Average periapsis radius is "<<
	fixed<<setprecision(2)<<pe_avg/n<<" km"<<endl;
	
    cout << "Largest periapsis radius is: "<<
	fixed<<setprecision(2)<<largest<<" km"<<endl;
    
    
    

    system("PAUSE"); return 0;

}

