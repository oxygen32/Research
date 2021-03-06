# include <fstream>
# include <iomanip>
# include <time.h>
# include <iterator>
# include "element.h"

int prompt(int &flag);
void populate(vector<vector<element>> &orderedByTag);
void addElement(vector<vector<element>> &orderedByTag);
void sortElement(vector<vector<element>> &orderedByTag,element repair);
void removeTag(vector<vector<element>> &orderedByTag);
void removeElement(vector<vector<element>> &orderedByTag);
void updateElement(vector<vector<element>> &orderedByTag);
void viewTagHistory(vector<vector<element>> orderedByTag);
void viewTagRecentAdd(vector<vector<element>> orderedByTag);
void viewOpenRepairs(vector<vector<element>> orderedByTag);
void traverseVector(vector<vector<element>> orderedByTag);
void sendToServer(vector<vector<element>> orderedByTag);
void writeToFile(vector<vector<element>> orderedByTag,int &flag);
int sync();
int delay(int millisec);

void main()
{ 
	int selection;
	vector<vector<element>> orderedByTag;
	int flag;
	//change to a GUI format here//
	
	cout << endl << right << setw(33)<< setfill('*') << " " << "Welcome to the Inventory Proccessing System" << left << setw(33) << setfill('*') << " " << endl;
	
	
	selection=prompt(flag);
	while (selection)
	{
		switch (selection)
		{
		case 1: if (flag)
				{
					populate(orderedByTag);
					addElement(orderedByTag);
					sendToServer(orderedByTag);
					cout << endl << "The repair has successfully been added" << endl << endl;
				}
				else
					cout <<"You do not have permission to add repairs at this time. Please try again momentarily"<< endl << endl;
			    selection=prompt(flag);
			    break;
		
		case 2: if (flag)
		     	{
			     	populate(orderedByTag);
				    removeTag(orderedByTag);
					sendToServer(orderedByTag);
					cout << endl <<"The service tag has successfully been removed" << endl << endl;
			    } 
			    else
					cout <<"You do not have permission to remove a service tag at this time. Please try again momentarily" << endl << endl;
				selection=prompt(flag);
				break;

		case 3:	if (flag)
				{
					populate(orderedByTag);
					removeElement(orderedByTag);
					sendToServer(orderedByTag);
					cout << endl << "The repair has successfully been remove" << endl << endl;
				}
				else
					cout <<"You do not have permission to remove a repair at this time. Please try again momentarily" << endl << endl;
				selection=prompt(flag);
				break;

		case 4: if (flag)
				{
					populate(orderedByTag);
					updateElement(orderedByTag);
					sendToServer(orderedByTag);
					cout << endl <<"The repair has successfully been updated" << endl << endl;
				}
				else
					cout <<"You do not have permission to remove a repair at this time. Please try again momentarily" << endl << endl;
				selection=prompt(flag);
				break;

		case 5: 
				if(flag)
				{
					cout << "This is the most current information available" << endl;
					populate(orderedByTag);
				}
				else
					cout << "The database is currently being updated. This information is from the last successful save" << endl;
				viewTagHistory(orderedByTag);
				selection=prompt(flag);
				break;

		case 6: 
				if(flag)
				{
					cout << "This is the most current information available" << endl;
					populate(orderedByTag);
				}
				else
					cout << "The database is currently being updated. This information is from the last successful save" << endl;
				viewTagRecentAdd(orderedByTag);
				selection=prompt(flag);
				break;

		case 7: 
				if(flag)
				{
					cout << "This is the most current information available" << endl;
					populate(orderedByTag);
				}
				else
					cout << "The database is currently being updated. This information is from the last successful save" << endl;
				viewOpenRepairs(orderedByTag);
				selection=prompt(flag);
				break;

		case 8:
				if(flag)
				{
					cout << "This is the most current information available" << endl;
					populate(orderedByTag);
				}
				else
					cout << "The database is currently being updated. This information is from the last successful save" << endl;
				traverseVector(orderedByTag);
				selection=prompt(flag);
				break;

		default:
			selection=prompt(flag);
		}
	}
}

	int prompt(int &flag)
	{
		ifstream inFile("InUseFlag.txt");
		inFile >> flag;
		inFile.close(); 
		int response;
		cout << "Please make a selection" << endl;
		cout << "(1) Add a new repair " << endl;
		cout << "(2) Remove a Service Tag " << endl;
		cout << "(3) Remove a repair " << endl;
		cout << "(4) Update a repair " << endl;
		cout << "(5) View a service tag's history " << endl;
		cout << "(6) View the most recent repair for a service tag " << endl;
		cout << "(7) View Open repairs " << endl;
		cout << "(0) EXIT" << endl;
		cin >> response;
		return response;
	}

	void populate(vector<vector<element>> &orderedByTag)
	{
		element repair;
		string text,part,name;
		char c[9];
		char tester;
    	ifstream inFile("MasterTextFile.txt");
		inFile.ignore(2);
		inFile >> tester;
		while (tester=='{')
		{
		inFile.ignore(1);
		inFile >> repair.serviceTag;
		inFile.ignore(2);
		inFile >> text;
		repair.transferLaptopModel(text);
		inFile.ignore(1);
		inFile >> text;
		repair.transferLaptopName(text);
		inFile.ignore(1);
		inFile >> text;
		repair.transferWarrantyStateDate(text);
		inFile.ignore(1);
		inFile >> text;
		repair.transferWarrantyEndDate(text);
		inFile.ignore(3);
		inFile >> c;
		repair.transferDateEntered(c);
		inFile.ignore(1);
		inFile >> repair.currentLocation;
		inFile.ignore(1);
		inFile >> text;
		repair.transferDispatchNumber(text);
		inFile.ignore(1);
		inFile >> text;
		repair.transferCaseNumber(text);
		inFile.ignore(1);
		inFile >> repair.callInTime;
		inFile.ignore(1);
		inFile >> repair.callOutTime;
		inFile.ignore(1);		
		getline(inFile,text);
		repair.transferTechName(text);
		inFile.ignore(2);
		getline(inFile,repair.partsAffected);
		inFile.ignore(2);
        getline(inFile,repair.techNotes);
	//	cout << endl ;
	//	repair.displayAll();
        sortElement(orderedByTag,repair);
		inFile.ignore(13);
		inFile >> tester;
	}
		inFile.close();
	}

void addElement(vector<vector<element>> &orderedByTag)
{//prompt for info
	element repair;
	int selection;
	char answer1;
	char answer2='y';
	do
	{
			repair.setAll();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~testing filling of data~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			cout << endl;
			repair.displayAll();
			cout << "Does any of the information need to be corrected? (y or n)" << endl;
			cin >> answer1;
			while(answer1=='y'||answer1=='Y')
			{
				cout << "Please make a selection" << endl;
				cout << "(1) service tag" << endl;
				cout << "(2) model number" << endl;
				cout << "(3) laptop name" << endl;
				cout << "(4) laptop namestarting date of the warranty(xx/xx/xxxx)" << endl;
				cout << "(5) ending date of the warranty(xx/xx/xxxx)" << endl;
				cout << "(6) current location" << endl;
				cout << "(7) technician's name" << endl;
				cout << "(8) change date entered to the current date" << endl;
				cout << "(9) dispatch number" << endl;
				cout << "(10) case number" << endl;
				cout << "(11) call in time" << endl;
				cout << "(12) call out time" << endl;
				cout << "(13) parts affected" << endl;
				cout << "(14) notes" << endl;
				cin >> selection;
				switch (selection)
				{
				case 1:	repair.setTag();
					break;
				case 2:	repair.setModel();
					break;
				case 3:	repair.setLaptopName();
					break;
				case 4:	repair.setStartDate();
					break;
				case 5:	repair.setEndDate();
					break;
				case 6: repair.setLocation();
					break;
				case 7:	repair.setTechName();
					break;
				case 8:	repair.setDateEntered();
					break;
				case 9:	repair.setDispatchNumber();
					break;
				case 10: repair.setCaseNumber();
					break;
				case 11: repair.setCallInTime();
					break;
				case 12: repair.setCallOutTime();
					break;
				case 13: repair.setPartsAffected();
					break;
				case 14: repair.setTechNotes();
					break;
				default:
					break;
				}
				repair.displayAll();
				cout << "Does any of the information need to be corrected? (y or n)" << endl;
				cin >> answer1;
			}				
	sortElement(orderedByTag,repair);
	cout << "Would you like to add another repair? (y or n) " << endl;
	cin >> answer2;
	}while(answer2=='y'||answer2=='Y');
}

void sortElement(vector<vector<element>> &orderedByTag,element repair)
{
/*Begins the search for the right place in the vector to add the repair. 
Starts at the begining of the vector. Searchs for the right place to insert the repair's data. 
Exits if a service tag is equal to or larger than the repair or if it reaches the end of the vector. 
Checking that i is less than the length ensures that there isn't a comparison outside of the subscripts of the vector.*/
	int i=0,j=0;
	int length=static_cast<int>(orderedByTag.size());
	if (orderedByTag.empty())
	{
		orderedByTag.resize(orderedByTag.size()+1);
        orderedByTag[0].push_back(repair);
	}
	else 
	{
		while((i<length) && orderedByTag[i][0].serviceTag<repair.serviceTag)
		{
			i++;
		}
/*if i has not reach the end then the service tag is equal to or smaller than a service tag already in the vector*/
		if (i!=length)
		{
/*if the service tag is found, searches for the right place in the embedded vector to add the repair*/
			if (orderedByTag[i][0].serviceTag==repair.serviceTag)
			{
				length=static_cast<int>(orderedByTag[i].size());
				orderedByTag[i].push_back(repair);				
			}
/*In this case  So the vector is resized to add in the service Tag. From the back of the vector the data is moved until the subscript i is reached; the 
subscript i where the new repair is added.*/	
			else
			{
				length=static_cast<int>(orderedByTag.size());
				orderedByTag.resize(length+1);
				for(j=length;j>i;j--)
				{	
					orderedByTag[j].resize(0);
					for(int k=0;k<static_cast<int>(orderedByTag[j-1].size());k++)
					{
						orderedByTag[j].push_back(orderedByTag[j-1][k]);
					}
				}
				orderedByTag[i].resize(0);
				orderedByTag[i].push_back(repair);
			}
		}
		else 
		{
/*In this case the service tag is not found. The vector is then resized and the new repair is added to the back.*/
			orderedByTag.resize(length+1);
			orderedByTag[length].push_back(repair);		
		}
	}
}


	void removeTag(vector<vector<element>> &orderedByTag)
	{
		char repeat;
		int first;
		int last;
		int mid;
		string target;
	
		do
		{
			
		last=static_cast<int>(orderedByTag.size());
		first=0;

		cout << endl <<"Please enter the service tag " << endl;
		cin >> target;

		while (first<last)
		{
			mid=(first+last)/2;
			if (orderedByTag[mid][0].serviceTag <target)
				first=mid+1;
			else if(orderedByTag[mid][0].serviceTag>target)
				last=mid;
			else
				break;
		}
		if (orderedByTag[mid][0].serviceTag!=target)
			cout << endl <<"This service tag is not valid or does not have a repair history" << endl;
		else
		{
			int	length=static_cast<int>(orderedByTag.size());
			for(int i=mid;i<length-1;i++)
			{	
					orderedByTag[i].resize(0);
					for(int j=0;j<static_cast<int>(orderedByTag[i+1].size());j++)
						orderedByTag[i].push_back(orderedByTag[i+1][j]);
			}
			orderedByTag.pop_back();
		}
		cout << "Would you like to remove another service tag? (y or n)" << endl;
		cin >> repeat;
	}while(repeat=='y'||repeat=='Y');
	}


	void removeElement(vector<vector<element>> &orderedByTag)
	{	
		char repeat,answer,response;
		char t_date[9];
		int selection;
		int first;
		int last;
		int mid,mid2;
		string target;

		
		do
		{
			
		last=static_cast<int>(orderedByTag.size());
		first=0;

		cout << endl <<"Please enter the service tag " << endl;
		cin >> target;

		while (first<last)
		{
			mid=(first+last)/2;
			if (orderedByTag[mid][0].serviceTag <target)
				first=mid+1;
			else if(orderedByTag[mid][0].serviceTag>target)
				last=mid;
			else
				break;
		}
		if (orderedByTag[mid][0].serviceTag!=target)
			cout << endl <<"This service tag is not valid or does not have a repair history" << endl;
		else
		{
			/*
			cout<<"Do you have the date of the repair to be deleted?(y or n)" <<endl;
			cin >> response;
			
			if(response=='y'||response=='Y')
			{
				cout << "Please enter the date. (XX/XX/XX)" << endl;
				cin >> t_date;
				first=0;
				last=orderedByTag[mid].size();
				while (first<last)
				{
					mid2=(first+last)/2;
					if (orderedByTag[mid][0].dateEntered <t_date)
						first=mid+1;
					else if(orderedByTag[mid][0].dateEntered >t_date)
						last=mid;
					else
						break;
				}
				if (orderedByTag[mid][mid2].dateEntered!=t_date)
					cout << endl <<"This service tag does not have a repair for the date entered" << endl;
				else
				{	// pushback will add to end resizint to mid2 will lose the data needed to pushback
					//int	length=static_cast<int>(orderedByTag.size());
					//for(int i=mid2;i<length;i++)
					//{	
					//	orderedByTag[mid][i].push_back(orderedByTag[mid][i+1]);
					//}
					//orderedByTag[mid].pop_back();
					
					orderedByTag[mid].erase(orderedByTag[mid][mid2]);
				}
			}
			else
			{*/
				for(int i=0;i<static_cast<int>(orderedByTag[mid].size());i++)
				{
					orderedByTag[mid][i].displayAll();
					cout << "Delete this repair? (y or n)" << endl;
					cin >> response;
					if(response=='y'||response=='Y')
					{
						orderedByTag[mid].erase(orderedByTag[mid].begin()+i);
						i--;
					}
				}
			//}
		}
			
		cout << "Would you like to remove another record from a different service tag? (y or n)" << endl;
		cin >> repeat;
		}while(repeat=='y'||repeat=='Y');
	}

	

	
	void updateElement(vector<vector<element>> &orderedByTag)//assumes that updating is for the most recent record only
	{
		char repeat;
		char answer;
		int selection;
		int first;
		int last;
		int mid;
		string target;

		
		do
		{
		last=static_cast<int>(orderedByTag.size());
		first=0;

		cout << endl <<"Please enter the service tag " << endl;
		cin >> target;

		while (first<last)
		{
			mid=(first+last)/2;
			if (orderedByTag[mid][0].serviceTag <target)
				first=mid+1;
			else if(orderedByTag[mid][0].serviceTag>target)
				last=mid;
			else
				break;
		}
		if (orderedByTag[mid][0].serviceTag!=target)
			cout << endl <<"This service tag is not valid or does not have a repair history" << endl;
		else
		{
			
			int	length=static_cast<int>(orderedByTag[mid].size());
			do
			{
				cout << "Please make a selection" << endl;
				cout << "(1) service tag" << endl;
				cout << "(2) model number" << endl;
				cout << "(3) laptop name" << endl;
				cout << "(4) laptop namestarting date of the warranty(xx/xx/xxxx)" << endl;
				cout << "(5) ending date of the warranty(xx/xx/xxxx)" << endl;
				cout << "(6) current location" << endl;
				cout << "(7) technician's name" << endl;
				cout << "(8) change date entered to the current date" << endl;
				cout << "(9) dispatch number" << endl;
				cout << "(10) case number" << endl;
				cout << "(11) call in time" << endl;
				cout << "(12) call out time" << endl;
				cout << "(13) parts affected" << endl;
				cout << "(14) notes" << endl;
				cin >> selection;
				switch (selection)
				{
					case 1:	orderedByTag[mid][length-1].setTag();
							break;
					case 2:	orderedByTag[mid][length-1].setModel();
							break;
					case 3:	orderedByTag[mid][length-1].setLaptopName();
							break;
					case 4:	orderedByTag[mid][length-1].setStartDate();
							break;
					case 5:	orderedByTag[mid][length-1].setEndDate();
							break;
					case 6: orderedByTag[mid][length-1].setLocation();
							break;
					case 7:	orderedByTag[mid][length-1].setTechName();
							break;
					case 8:	orderedByTag[mid][length-1].setDateEntered();
							break;
					case 9:	orderedByTag[mid][length-1].setDispatchNumber();
							break;
					case 10: orderedByTag[mid][length-1].setCaseNumber();
							break;
					case 11: orderedByTag[mid][length-1].setCallInTime();
							break;
					case 12: orderedByTag[mid][length-1].setCallOutTime();
							break;
					case 13: orderedByTag[mid][length-1].setPartsAffected();
							break;
					case 14: orderedByTag[mid][length-1].setTechNotes();
							break;
					default:
							break;
				}
			orderedByTag[mid][length-1].displayAll();
			cout << "Would you like to update any other information for this record? (y or n)" << endl;
			cin >> answer;
		}while(	answer=='y'||answer=='Y');
		}
		cout << "Would you like to update a other record? (y or n)" << endl;
		cin >> repeat;
	}while(repeat=='y'||repeat=='Y');
	}

void viewTagHistory(vector<vector<element>> orderedByTag)
{
	int first=0;
	int last=static_cast<int>(orderedByTag.size());
	int mid; 
	string target;

	cout << endl << "Please enter the service tag " << endl;
	cin >> target;

	while (first<last)
	{
		mid=(first+last)/2;
		if (orderedByTag[mid][0].serviceTag <target)
			first=mid+1;
		else if(orderedByTag[mid][0].serviceTag>target)
			last=mid;
		else
			break;
	}
if (orderedByTag[mid][0].serviceTag!=target)
	cout << endl << "This service tag is not valid or does not have a repair history" << endl;
else
{
	cout << endl << right << setw(47)<< setfill('*') << " "<< "HISTORY FOR " << target << left<< setw(47)<<setfill('*') <<" "<< endl;
	orderedByTag[mid][0].displayOne();
	cout << endl;
	for (int j=0;j<static_cast<int>(orderedByTag[mid].size());j++)
	{
		orderedByTag[mid][j].displayTwo();
		cout << endl;
	}
}
}


void viewTagRecentAdd(vector<vector<element>> orderedByTag)
{
	int first=0;
	int last=static_cast<int>(orderedByTag.size());
	int mid;
	string target;

	cout << endl <<"Please enter the service tag " << endl;
	cin >> target;

	while (first<last)
	{
		mid=(first+last)/2;
		if (orderedByTag[mid][0].serviceTag <target)
			first=mid+1;
		else if(orderedByTag[mid][0].serviceTag>target)
			last=mid;
		else
			break;
	}
	if (orderedByTag[mid][0].serviceTag!=target)
		cout << endl <<"This service tag is not valid or does not have a repair history" << endl;
	else
	{
		int	length=static_cast<int>(orderedByTag[mid].size());
		cout << endl << right << setw(42)<< setfill('*') << " "<< "MOST RECENT REPAIR FOR " << target << left<< setw(42)<<setfill('*') <<" "<< endl;
		orderedByTag[mid][length-1].displayAll();
	}
}

void viewOpenRepairs(vector<vector<element>> orderedByTag)
{
	unsigned int i;
	unsigned int length=orderedByTag.size();
	cout << endl << right << setw(44)<< setfill('*') << " "<<"LIST OF OPEN REPAIRS" << left<< setw(44)<<setfill('*') <<" "<<endl;
	for (i=0;i<length;i++)
	{
		if(orderedByTag[i][orderedByTag[i].size()-1].currentLocation!="Circulation")
		{
			cout << endl;
			orderedByTag[i][orderedByTag[i].size()-1].displayAll();
			cout << endl;
		}
}
}

void traverseVector(vector<vector<element>> orderedByTag)//for testing , possible for "show all repair history"
{cout<<"Testing traversing the vector"<< endl;
unsigned int i,j;
for(i=0;i<orderedByTag.size();i++)
	for(j=0;j<orderedByTag[i].size();j++)
	{cout << "index 1: " <<i <<"index 2: " <<j;//testing
		cout << endl;
	//	orderedByTag[i][j].displayAll();		
		orderedByTag[i][j].getTag();
		orderedByTag[i][j].getLocation();
		orderedByTag[i][j].getDateEntered();
		orderedByTag[i][j].getTechNotes();
		cout << endl;
	}
}
void sendToServer(vector<vector<element>> orderedByTag)
{
	int flag;
	writeToFile(orderedByTag,flag);
	while (flag==-1)
	{
		writeToFile(orderedByTag,flag);
	}
	//when the loop cont. server is down flag=0
}
void writeToFile(vector<vector<element>> orderedByTag,int &flag)
{
	ofstream outFile("TempText.txt");
	outFile << "!" << endl;
    string text;
	for (int i=0;i<static_cast<int>(orderedByTag.size());i++)
	{
		for(int j=0;j<static_cast<int>(orderedByTag[i].size());j++)
		{
			outFile << "{ " << orderedByTag[i][j].serviceTag << endl;
			outFile << "( " ;
			orderedByTag[i][j].writeLaptopModel(text);
			outFile << text << " " ;
			orderedByTag[i][j].writeLaptopName(text);
			outFile << text << " " ;
			orderedByTag[i][j].writeWarrantyStateDate(text);
			outFile << text << " " ;
			orderedByTag[i][j].writeWarrantyEndDate(text);
			outFile	<< text << " " << endl;
			outFile << "[ ";
			orderedByTag[i][j].writeDateEntered(text);
			outFile << text << " " ;
			outFile << orderedByTag[i][j].currentLocation << " " ; 
			orderedByTag[i][j].writeDispatchNumber(text);
			outFile << text << " " ;
			orderedByTag[i][j].writeCaseNumber(text);
			outFile << text << " " ;
			outFile << orderedByTag[i][j].callInTime <<" " << orderedByTag[i][j].callOutTime<<" ";
			orderedByTag[i][j].writeTechName(text);
			outFile << text << " "<< endl;
			outFile << "< " << orderedByTag[i][j].partsAffected << endl ;
			outFile << "# " << orderedByTag[i][j].techNotes << endl;
			outFile << "> " << endl;
			outFile << "& " << endl;
			outFile << "] " << endl; 
			outFile << ") " << endl;
			outFile << "} " << endl << endl;
		}
	}
	outFile << "-" << endl;
	outFile.close();
	flag=sync();
}
int sync()
{
	//send message for server to change flag--0 while working(checking and updating),-1 error, 1 success.
	ifstream inFile("SuccessFlag.txt");
	int flag,i=0;
	inFile >> flag;
	inFile.close();
	while (flag==0 && i<20)
	{
		i++;
		delay(10000); //how long of a wait?? 10sec??
		inFile.open("SucessFlag.txt");
		inFile >> flag;
		inFile.close();
		
	}
return flag;
}

int delay(int millisec)
{
clock_t timesec;

timesec = clock();

while((clock() - timesec) < millisec)
{
}

return millisec;

}

