#ifndef NMEAParser_h
#define NMEAParser_h

public class NMEAParser
{
	public:
		NMEAParser();
		~NMEAParser();
		void parse(char** gps);
		float getAltitude();
		float getLatitude();
		float getLongitude());
		
	private:
		void parseGPGAA(char** gpgaa);
		void parseGPGLL(char** gpgll);
		void parseGPGSV(char** gpgsv);
		
		//Member variables
		float altitude, minLatitude, minLongitude;
		int degLatitude, degLongitude;
		float gdop;
		unsigned char numSatellites;
}

#endif