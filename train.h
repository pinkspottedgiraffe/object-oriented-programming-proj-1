class waggons;
class commuter;

const int totalWaggons=5;

class waggons{
	int numofpeople;
	commuter** comarray;
	int check;
	float waggonfines;
	int notickets1;		//number of people who were found with no tickets who aren't entitled to a concession
	int notickets2;		//number of people who were found with no tickets who are entitled to a concession
	int notcaught;
	
	public:
		waggons();
		~waggons();
		int inStation();
		int betweenStations();
		void printStatistics();
		int addcom(int);
		int rmvcom(int);
		int getpeople(){
			return numofpeople;
		}
		float get_fines(){
			return waggonfines;
		}
		void remove_all_com();
};


class train{
	int stations;
	float fines;
	waggons waggons_Array[totalWaggons];
	
	public:
		train(int);
		~train();
		void printStatistics();
		int operate();
};



class commuter{
	int ticket;		//1 if they have ticket, 0 if they don't
	int concession;	//1 if they are entitled to concession 0 if they are not
	int checked;	//1 if ticket was checked, 0 if it wasn't
	
	public:
	commuter();
	int get_ticket();
	int get_concession();
	void setchecked();
	int getchecked();
	~commuter();
};
