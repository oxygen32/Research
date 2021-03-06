//creating server that will work with client program. Will work multiclient. 
#include<iostream>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include "template.h" //checks to see if vector is in right format
using namespace std;


void DATA_BACKUP()//this will be operating system dependent 
{
string sys,temp;
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );//getting the time
  timeinfo = localtime ( &rawtime );
  temp=asctime(timeinfo);
  temp.erase(0, 4);
  
  for(int i=0;i<temp.size();i++)//sets it to a way that the computer can use via command line
{	if(temp[i]==' '||temp[i]==':')
		temp[i]='_';
}
temp+=".txt";
temp="\\"+temp;
temp.erase(0,0);
sys=("copy MasterTextFile.txt \BACKUP")+temp;//timestamp

cout<<endl<<"temp :"<<sys<<endl;
system(sys.c_str());							//timestamped copy put into BACKUP folder 
};



bool is_any_text()//checks to see if all .txt files are there. If not, prints out which ones are not there and exits server. If there, goes though rest of operations.
{
     bool is_any=true;
     ifstream myfile("MasterTextFile.txt");
	if (myfile.is_open()) 
 {
//   cout<<"MasterTextFile.txt here: "<<endl;
 }   
else {cout<<endl<<"ERROR: cannot access MASTER_DATABASE! Contact systems administrator! "<<endl;
      is_any=false;}    
 myfile.close();
//**********************************
     ifstream fl("InUseFlag.txt");
	if (fl.is_open()) 
 {
//   cout<<"InUseFlag.txt here: "<<endl;
 }   
else {cout<<endl<<"ERROR: cannot access InUseFlag.txt! Contact systems administrator! "<<endl;
      is_any=false;}    
 fl.close();     
//**********************************
     ifstream su("SuccessFlag.txt");
	if (su.is_open()) 
 {
//   cout<<"SuccessFlag.txt here: "<<endl;
 }   
else {cout<<endl<<"ERROR: cannot access SuccessFlag.txt! Contact systems administrator! "<<endl;
      is_any=false;}    
 su.close();  
//**********************************
     ifstream temp("TempText.txt");
	if (temp.is_open()) 
 {
//   cout<<"TempText.txt here: "<<endl;
 }   
else {cout<<endl<<"ERROR: cannot access TempText.txt! Contact systems administrator! "<<endl;
      is_any=false;}    
 temp.close();   
//**********************************
    ifstream op("OpText.txt");
    if (op.is_open())
    {
                     //cout<<"operation file here"<<endl;      
    }
else {cout<<endl<<"ERROR: cannot access OpText.txt! Contact systems administrator! "<<endl;
is_any=false;}
op.close();
//**********************************
    ifstream ser("server_cmds.txt");
    if (ser.is_open())
    {
                     //cout<<"server_cmds.txt file here"<<endl;      
    }
else {cout<<endl<<"ERROR: cannot access server_cmds.txt! Contact systems administrator! "<<endl;
is_any=false;}
ser.close();
return is_any;     
};

bool is_temptxt()//checks to see if there is operation occuring
{
     string flag;
  ifstream myfile ("OpText.txt");//finds out if there is a ! in op.txt, then return true
     myfile>>flag;
     myfile.close();
     
     if(flag=="!")
     return true;
     else return false;    
};

void success_st()//servers busy 
{
ofstream flg ("SuccessFlag.txt");
flg <<0 ;    
flg.close();           
};


void pop_vec(vector<string> &popu)
{
     string temp;
       ifstream myfile ("TempText.txt");
         while(!myfile.eof()) 
         {
         getline(myfile,temp);
         popu.push_back(temp);                           
         }
}

void error()
{
ofstream flg ("SuccessFlag.txt");
flg <<-1;     
flg.close();        
ofstream use ("InUseFlag.txt");
use <<0;       
use.close();           
};

bool server_cmds()
{
 string temp;
 ifstream cmds ("server_cmds.txt");
 getline(cmds,temp);
 cmds.close();    
     if(temp=="stop")
     return false;
     else
     return true;     
}
void shutdown_server_cmds()
{
ofstream cmds ("server_cmds.txt");
cmds<<"reset";
cmds.close();
}
void reset()
{
string temp="reset";
ofstream myfile("TempText.txt");//resets file
myfile<<temp;     
myfile.close();
     
ofstream use ("InUseFlag.txt");
use <<0;//server not in use       
use.close();    
     
ofstream flg ("SuccessFlag.txt");
flg <<1; //servers done with operation without errors    
flg.close();      

ofstream op("OpText.txt");//resets file
op<<temp;     
op.close();     
};
void save_to_master(vector<string> mast)
{
     ofstream myfile("MasterTextFile.txt");
     for(int i=0;i<mast.size();i++)
     {
     myfile<<mast[i]<<endl;    
     }
     myfile.close();
     
}

int main()
{
    vector<string> test;
    format fm;
    string servercmd;
    int counter=0,refresh=0;   
    cout<<"starting server:"<<endl;
    
    
while(server_cmds() && is_any_text())//as long as there are txt files and server command is not "stop", then server keeps going 
{
                        
                        
 if(is_temptxt())
 {
   success_st();
   pop_vec(test); //populates the vector with information                            
                
                if(!fm.is_right(test))
                {
                      
                      cout<<"corruption of test file, error being sent to client"<<endl;
                      error();//creates error statement
                      }
                      else 
                      {
                           counter++;
                           cout<<"operation detected, no problems found, saving to MasterTxtFile"<<endl;
                           save_to_master(test);
                           reset();//resets everything
                           
                      }           
                      test.clear();
                   
  }
  else
  cout<<"no operations detected"<<endl;
  
  if(refresh==9)
  {
  system("cls");              
  refresh=0;              
  }
  if(counter==9)//every 10 counters, timestamp data and back it up.
  {
  DATA_BACKUP();               
  counter=0;//reset counter               
  }
 Sleep(500);
 refresh++;
}  


cout<<"stopping server and saving files: "<<endl;
DATA_BACKUP();//will always backup before server stops
shutdown_server_cmds();//resets server_cmds.txt
    system("pause");
    
return 0;    
} 
