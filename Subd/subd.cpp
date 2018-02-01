#include <iostream>
#include <fstream> 
#include <map> 
#include <string.h> 
#include <vector> // ymnii massiv
#include <iomanip>//dlya vydeleniya prostranstva pod vyvod
#include <stdlib.h>
#include <cmath>//for using math formuls
#include <ctime> //dlya vremeni
using namespace std;
typedef map < string , void* > row; //tip gde hranitsya Db_table
typedef map <string, string> header; //tip gde hranitsya zagolovok bazi_dannih
const int kol_type = 5;
const int kol_detalei = 10;
const int kol_tabliz = 4;
const int max_kol_simvolov_v_file=250;
struct Type_detali //struktura dlya binarnika
{
   int partia;
   int nomer;
   int zhestkosti;
};
class Binarnoe_schitivanie 
{
	private:
	Type_detali detali[kol_detalei]; //inizilizorovanii massiv kotorii mi zapisivaem v file
	Type_detali detali_second[kol_detalei]; //ne inizilizorovanii massiv kotorii mi zapisivaem v file
	public:
	Binarnoe_schitivanie()
	{
		srand(time(0)); 
		for(int i=0; i<kol_detalei; i++)
		{
			                            //zapolniem masiv detalei
			detali[i].nomer=rand() %100;// slychainimi chislami
			detali[i].partia=rand() %100;
			detali[i].zhestkosti=rand() %100; 
		}
	}
	void pokazati() //show defined array
	{
		for(int i=0; i<kol_detalei; i++)
		 cout<<detali[i].nomer<<"__"<<detali[i].partia<<"__"<<detali[i].zhestkosti<<"__"<<endl;
		
	}
	void pokazati_2() //show array which we read from file
	{
		for(int i=0; i<kol_detalei; i++)
		 cout<<detali_second[i].nomer<<"__"<<detali_second[i].partia<<"__"<<detali_second[i].zhestkosti<<"__"<<endl;
		
	}
    void write_in_file() //put in file defined array
    {
	 ofstream f_write("detali.bin",ios::binary|ios::out);
	 f_write.write((char*)detali,sizeof(detali));
	}
   
   void get_in_memory() //get from file defined array
   {  
	 ifstream f_read("detali.bin",ios::binary|ios::in);
	 f_read.read((char*)detali_second,sizeof(detali_second));
   } 
   void change_in_file()
   {
	   int number_in_array=0,number_structure=0;//number-это число на которое мы заменить поле структуры
	   int* number=new int;
	   *number=0;
	   cout<<"Введите номер элемента массива структур,который хотите изменить "<<endl;
	   cin>>number_in_array;
	   cout<<"Введите порядковый номер поля структуры ";
	   cin>>number_structure;
	   cout<<"Введите число на которое вы хотите заменить поле структуры "<<endl;
	   cin>>*number;
	   ofstream f_write("detali.bin",ios::binary|ios::in | ios::out);
	   f_write.seekp(0); //указатель на начало файла
	   
	   f_write.seekp(sizeof(Type_detali)*number_in_array+sizeof(int)*number_structure); //устанавливаем указатель на новое место
	   f_write.write((char*)number,sizeof(int));  
   }
   int get_in_memory_count()
   {
	   int number_in_array=0,number_structure=0;//number-это число на которое мы заменить поле структуры
	   int* number=new int;
	   *number=0;
	   cout<<"Введите номер элемента массива структур,который хотите заполучить "<<endl;
	   cin>>number_in_array;
	   cout<<"Введите порядковый номер поля структуры ";
	   cin>>number_structure;
	   ifstream f_read("detali.bin",ios::binary | ios::in);
	   f_read.seekg(0); //указатель на начало файла
	   f_read.seekg((sizeof(Type_detali)*number_in_array+sizeof(int)*number_structure)); //устанавливаем указатель на нужное место 
	   f_read.read((char*)number,sizeof(int)); //читаем лишь то, что нам нужно
	   return *number;  //возвращаем значение
   }
};

class Db_date //класс времени
{
	private:
	int year;
	int month;
	int day;
	int all_days_from_zero;
	bool  leap_year_or_not; //1-это значит високостный 0 это значит не вискостный
	public:
	Db_date(char* date)
	{
		
		day=atoi(strtok(date,"."));
		month=atoi(strtok(NULL,"."));
		year=atoi(strtok(NULL,"."));
		from_data_to_days_from_zero();
	}
	Db_date()
	{
	}
	void show_days()
	{
		cout<<endl<<"****"<<all_days_from_zero;
	}
	void in_all_days_out_year_months_days()
	//эта функция принимает на вход общее число дней от рождества христова
	//и возвращает уже ,високосен ли год;номер года,номер месяца и номер
	//дня
	{
		//float approximate_year=all_days_from_zero/365;
		//year=roundf(approximate_year+0.5);
		int quantity_days_in_months[12]={ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		int month_and_day=all_days_from_zero;
		int year_it=1;
		year=0;
		month=0;
		day=0;
		while((month_and_day>366) || ((year_it+1)%4 == 0 && (year_it+1)%100 != 0) || 
		   ((year_it+1)%400 == 0))
		   {
			if ((((year_it+1)%4 == 0) && (year_it+1)%100 != 0) || 
		     ((year_it+1)%400 == 0))month_and_day-=366;
			   else month_and_day-=365;
			year_it++;
		   }
		year=year_it;
		if ((year%4 == 0 && year%100 != 0) || 
		   (year%400 == 0)) leap_year_or_not=1;
		        else leap_year_or_not=0;
		if (leap_year_or_not==0) quantity_days_in_months[1]=28;
		int i=0;
		while ((i<12) && (month_and_day>quantity_days_in_months[i]))
		{
			month_and_day-=quantity_days_in_months[i];
			cout<<endl<<"i="<<i;
			++i;
			//cout<<endl<<"deni i mesiz"<<month_and_day<<"kolichestvo dney v mesize"<<quantity_days_in_months[i]<<endl;
		}
		month=i;
		day=month_and_day;
	}
	void from_data_to_days_from_zero()
	{
		//Эта функция принимает на вход дату и преобразует
		//ее в количество дней от рождества
		//христова
		int quantity_days_in_months[12]={ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		all_days_from_zero=0;
		int year_it=year-1;
		
		if ((((year)%4 == 0) && (year)%100 != 0) || 
		    ((year)%400 == 0)) leap_year_or_not=1; else leap_year_or_not=0; //1)узнаем високостный год или 
		   if (leap_year_or_not==0) quantity_days_in_months[1]=28;          //обычный если обычный то меняем число дней в феврале
		
		while(year_it>0)
		   {
			if ((((year_it)%4 == 0) && (year_it)%100 != 0) ||   //2)находим количество дней содрежащееся
		     ((year_it)%400 == 0)) all_days_from_zero+=366;     //в годах без месяцев и дней
			   else all_days_from_zero+=365;
			year_it--;
		   }
		   
		   int i=month-1;
		   while (i>0)
		   {
			  all_days_from_zero+=quantity_days_in_months[i-1]; //находим количество дней которое находилось в месяцах
		      i--;
		   } 
		   all_days_from_zero+=day;
	}
	void print_all_days_and_date()
	{
		cout<<endl<<all_days_from_zero;
		cout<<endl<<day<<" : "<<month<<" : "<<year;
	}
	Db_date operator +(int X )
    {
     Db_date T;
     T.all_days_from_zero= this->all_days_from_zero + X;
     T.in_all_days_out_year_months_days();
     return T;
    }
    Db_date operator -(int X )
    {
     all_days_from_zero= this->all_days_from_zero - X;
     in_all_days_out_year_months_days();
    }
    Db_date operator -=(int X )
    {
     all_days_from_zero-=X;
     in_all_days_out_year_months_days();
   
    }
    Db_date operator +=(int  X )
    {
     
     all_days_from_zero=all_days_from_zero+X;
     in_all_days_out_year_months_days();
    }
    Db_date& operator ++()
    {
     all_days_from_zero++;
     in_all_days_out_year_months_days();
     return *this;
    }
    Db_date& operator ++(int NOT_USED)
    {
	Db_date T=*this;
    all_days_from_zero++;
    in_all_days_out_year_months_days();
     return T;
    }
    Db_date& operator --(int NOT_USED)
    {
	Db_date T=*this;
    all_days_from_zero--;
    in_all_days_out_year_months_days();
     return T;
    }
    Db_date& operator --()
    {
     all_days_from_zero--;
     in_all_days_out_year_months_days();
     return *this;
    }
    bool operator ==(Db_date & obj) 
    {
      if (all_days_from_zero == obj.all_days_from_zero) return true;
         else return false;
    }
    bool operator >(Db_date & obj) 
    {
      if (all_days_from_zero > obj.all_days_from_zero) return true;
         else return false;
    }
    bool operator <(Db_date & obj) 
    {
      if (all_days_from_zero < obj.all_days_from_zero) return true;
         else return false;
    }
    bool operator >=(Db_date & obj) 
    {
      if (all_days_from_zero >= obj.all_days_from_zero) return true;
         else return false;
    }
    bool operator <=(Db_date & obj) 
    {
      if (all_days_from_zero <= obj.all_days_from_zero) return true;
         else return false;
    }
    friend ostream & operator << ( ostream & out , Db_date & obj )
    {
     out << obj.day<<':'<<obj.month<<':'<<obj.year;
	 return out;
	}
	friend istream & operator >> ( istream & in , Db_date & obj )
    {
	 cout<<"Введите день месяц и год через пробел";
     in>>obj.day>>obj.month>>obj.year;
     while (obj.month>12)
     {
		 cout<<endl<<"ошибка количество месяцев не должно быть больше 12 повторить ввод месяца";
		 in>>obj.month;
	 }
	 obj.from_data_to_days_from_zero();
	 return in;
	}
};

class Db_table //sistema upravlenia bazi dannih 
{
private:
	string tableName; 
	header head_of_file;
public:
     
    vector < row > data;//tut hranyatsya nashi dannye
    
    int finds_interval_only_for_orders(Db_date date1,Db_date date2,vector<int>& zakazi)
    {
		if (tableName!="Orders.txt")                       
		{
			 cout<<"Это функция только для таблицы Orders";
			 return -1;
		}
		for (int i=0; i < data.size(); i++) //cikl po vsem ehlementam vektora
		{
			if ((*((Db_date*)data[i]["OrderDate"])<date2) && (*((Db_date*)data[i]["OrderDate"])>date1))
			   zakazi.push_back(i);
		}
		
		
	}
	//оптовая цена
	double product_price_only_for_products(int i)
	{
		return *((double*)data[i]["UnitPrice"]);
		
	}
	void* GetValue(string col_name, char* value) //colName-imya stolbca,value -znachenie   
	{
			
		string  types[kol_type] = { "Notype","Int","String","Double","Db_date" }; //kakie tipy
		int triger; //dlya svitch kejsa
		int i;
		
		for (i = 0; i < kol_type; i++)
			if (col_name == types[i])
			   triger = i; //opredelyaem tip
		double* b;       //tipi 
		string* buffer;  //     kotorie mi ispolizyem
		int* a;          //                            v switchcase
		Db_date* date;
		switch (triger)
		{
		case 0:
			return NULL;
			break; // vozvrashchaem NULL esli bez tipa
		case 1:
			a = new int(atoi(value));
			return a; //vozvrashchaem int
			break;
		case 2:
			buffer = new string(value);
			return buffer;
			break;
		case 3:
			b = new double(atof(value));
			return b;
			break;
		case 4:
		    date = new Db_date(value);
			return date;
			break;
		default:
			cout << "Notype";
			return NULL;
		}
	}

	int read_table() //функция возвращает значение значение 0 если файл был успешно открыт или если не был открыт то возвращет -1
	{
		ifstream fread; //schitat' iz fajla
		fread.open(tableName.c_str()); // Otkrytie fajla dlya chteniya
		if(fread.is_open())
		    cout<<endl<<"Файл успешно открыт"<<endl;
		 else
		  {
			  cout<<endl<<"Файл открыт не был экстренное завершение"<<endl;
			  return -1;
		  }
		vector <string> header;// tut my hranim header
		char line[500];// tut hranim samu schitannuyu iz fajla stroku
		char* token; // ukazatel dlya hraneniya slova stroki
		fread.getline(line, 500,'\n');
		token = strtok(line, "|\n");
		while (token != NULL)
		{
			header.push_back(token); //schityvaem v vektor vsyu stroku kazhdoe slovo ehto 
            token = strtok(NULL, "|\n");		
		}
		for (unsigned int i = 0; i<header.size(); i += 2)
		{
			head_of_file[header[i]] = header[i + 1];
		}

		row temp;
		
		while (fread.getline(line, 250))
		{
			//buf = line;
			int i = 0;
			token = strtok(line, "|\n");
			//int iter=0;
			while (token!= NULL)
			{
				temp[header[i]] = GetValue(header[i + 1], token);
				i += 2;
				token = strtok(NULL, "|\n");
			}
			data.push_back(temp);
			
		}
		return 0; 
	}
	void print_table()
	{
		
		
		for (int i = 0; i < 100; i++)              //pechataem razdelyayushchuyu
			cout << "=";                      // stroki
		//map<string, string>::iterator i3 = this->head_of_file.begin(); //tut my pechataem
		cout<<endl;
		for (map<string, string>::iterator i3 = head_of_file.begin(); i3 != head_of_file.end(); i3++) //polya tablicy
		{
			cout << setw(20) << i3->first;
		}
		cout<<endl;
		string  types[kol_type] = { "Notype","Int","String","Double","Db_date" }; //kakie tipy
		
		int triger; //dlya svitch kejsa
		
		for (int/*size_t*/ i=0; i < data.size(); i++) //cikl po vsem ehlementam vektora
		{ 
			
			//map<string, void*>::iterator i2 = this->data[i].begin(); //opredelyaem iterator
			for (map<string, void*>::iterator i2 = data[i].begin(); i2 != data[i].end(); i2++) //cikl po vsem ehlementam map
			{
				
				for (int i4 = 0; i4 < kol_type; i4++) //head_of_file[i2->first] //opredelyaem tip
					if (head_of_file[i2->first] == types[i4]) triger = i4; 
				switch (triger)
				{
				case 1:
					cout  << setw(20) << *((int*)data[i][i2->first]);
					break;
				case 2:
					cout  <<setw(20) << *((string*)data[i][i2->first]);
					break;
				case 3:
				    cout.clear();
					cout  << setw(20) << *((double*)data[i][i2->first]);
					break;
				case 4:
				    cout.clear();
					cout  << setw(10) << *((Db_date*)data[i][i2->first]);
					break;	
				default:
					cout << "No this tupe";
					break;
				}
				
			}
		    cout<<endl;
		}
	}
	void write_table() //запись в файл
	{
	   char* recordable_file_name; //file name where we write
	   recordable_file_name=new char[250];
	   cout<<endl<<"Введите имя файла,куда нужно записать базу данных";
	   cin>>recordable_file_name;
	   fstream fout(recordable_file_name);
	   for (map<string, string>::iterator i3 = head_of_file.begin(); i3 != head_of_file.end(); i3++) //polya tablicy
		{
			
			fout<<i3->first<<'|'<<i3->second<<'|';  
		}
	   fout<<endl;
	   string  types[kol_type] = { "Notype","Int","String","Double","Db_date" }; //kakie tipy
		
		int triger; //dlya svitch kejsa
		
		for (size_t i=0; i < data.size(); i++) //cikl po vsem ehlementam vektora
		{ 
			
			//map<string, void*>::iterator i2 = this->data[i].begin(); //opredelyaem iterator
			for (map<string, void*>::iterator i2 = data[i].begin(); i2 != data[i].end(); i2++) //cikl po vsem ehlementam map
			{
				
				for (int i4 = 0; i4 < kol_type; i4++) //head_of_file[i2->first] //opredelyaem tip
					if (head_of_file[i2->first] == types[i4]) triger = i4; 
				switch (triger)
				{
				case 1:
					fout<< *((int*)data[i][i2->first])<<'|';
					break;
				case 2:
					fout<< *((string*)data[i][i2->first])<<'|';
					break;
				case 3:
					fout<< *((double*)data[i][i2->first])<<'|';
					break;
				default:
					fout << "No this tupe"<<'|';
					break;
				}
				
			}
		    fout<<endl;
		}
	}
	void put_table_name(string table__name)
	{
	 tableName=table__name;
	}
};

class Db_table_set //множество таблиц
{
	private:
	string db_table_set_name; //имя файла где хранятся имена набора таблиц
	map<string,Db_table> db_set;
	public:
	
	double dohod_companii(Db_date first_date,Db_date second_date)
	{
		vector<int> zakazi;
		double dohod=0;
		db_set["Orders.txt"].finds_interval_only_for_orders(first_date,second_date,zakazi);
		for (unsigned int i=0; i<zakazi.size(); i++)
		 {
			 dohod+=*((int*)db_set["OrderDetails.txt"].data[zakazi[i]]["Quantity"])*(*((double*)db_set["OrderDetails.txt"].data[zakazi[i]]["UnitPrice"])-db_set["Products.txt"].product_price_only_for_products(*((int*)db_set["OrderDetails.txt"].data[zakazi[i]]["ProductID"])));
			 
		 }
		return dohod;
		
	}
	
	Db_table_set()
	{
		cout<<"Введите имя файла,в котором хранятся имена файлов с данными";
		cin>>db_table_set_name;
		fstream fin(db_table_set_name.c_str()); //создаем поток с файлом где хранятся имена файлов
		char* line;
		line=new char[max_kol_simvolov_v_file];
		while (fin.getline(line, 250))
		{
			cout<<line;
			db_set[line].put_table_name(line);
			db_set[line].read_table();
		}
	}
	Db_table& operator [](string Db_table_name) {return db_set[Db_table_name];}
	void read_all_tables()
	{
		fstream fin(db_table_set_name.c_str()); //создаем поток с файлом где хранятся имена файлов
		char* line;
		line=new char[max_kol_simvolov_v_file];
		while (fin.getline(line, 250))
		{
			db_set[line].read_table();
		}
	cout<<"Cчитывание прошло успешно"<<endl;
	}
	void write_all_tables_in_another_files() //мы записываем все таблицы в файл 
	{
		fstream fin(db_table_set_name.c_str()); //создаем поток с файлом где хранятся имена файлов
		char* line;
		line=new char[max_kol_simvolov_v_file];
		while (fin.getline(line, 250))
		{
			db_set[line].write_table();
		}
	}
	void print_all_tables_in_another_files()
	{
		fstream fin(db_table_set_name.c_str()); //создаем поток с файлом где хранятся имена файлов
		char* line;
		line=new char[max_kol_simvolov_v_file];
		while (fin.getline(line, 250))
		{
			db_set[line].print_table();
		}
	}
};

int main()
{
	int variant;
	/*
	Binarnoe_schitivanie raznie_detali ;
	
	//menu
	    cout<<"Вы хотите начать считывание бинарного файла? any key/n ";
	    
	    cin>>variant;
		while(variant!='n')
		{
			cout<<"1)Записать структуру в файл"<<endl;
			cout<<"2)Считать структуру из файл"<<endl;
			cout<<"3)Вывести иицилизированый массив, который мы записываем в файл"<<endl;
			cout<<"4)Вывести массив который мы считали из файла"<<endl;
			cout<<"5)Изменить какой либо элемент в файле"<<endl;
			cout<<"6)Вывести нужное значение из файла"<<endl;
			cin>>variant;
		switch(variant)
			{
			case '1':
				raznie_detali.write_in_file();
				cout<<"Запись в файл прошла успешно"<<endl;
				break;
			case '2':
				raznie_detali.get_in_memory();
				cout<<"Считывание из файла прошло успешно"<<endl;
				break;
			case '3':
				raznie_detali.pokazati();
				break;      
			case '4':
				raznie_detali.pokazati_2();
				break;
			case '5':
			    raznie_detali.change_in_file();
			    break;
			case '6':
			    cout<<endl<<raznie_detali.get_in_memory_count()<<endl;
			    break;
			case 'n':
			    break;
			default :
				cout<<"Нет такой команды повторите ввод";
			}    
			cout<<"================================="<<endl;
		}
    //menu	
    */
	int chislo;
	Db_table_set DB_opt;
	//запускается конструктор Db_table_set	
     cout<<"Вы хотите начать работу с BD? any 1-yes/0-no";
	    cin>>chislo;
	while(chislo)
		{
			cout<<"1)Распечатать все таблицы в другой файл";
			cout<<endl<<"2)Получить доход в указанный период(индивидуальное задание)";
			cout<<endl<<"3)Распечатать таблицы";
			
			cin>>chislo;
			
			Db_date first_date,second_date;
			switch(chislo)
			{
			case 1:
			   
               break;
			case 2:
			   
			   cout<<endl<<"1 дата из указанного периода"<<endl;
			   cin>>first_date;
			   cout<<endl<<"2 дата из указанного периода"<<endl;
			   cin>>second_date;
			   cout<<endl<<DB_opt.dohod_companii(first_date,second_date)<<endl;
			   cout.clear();   
               break;
			case 3:
			   DB_opt.print_all_tables_in_another_files();
			   break;
		    default :
			   cout<<"Нет такой команды повторите ввод"<<endl;
			   break;
			case 4:
			   chislo=0;
			   break;
		    
		    }
		}
     
     
    
    
    
    Db_date date_of_something,date_of_something2;
    cout<<"Вы хотите начать работу с Db_time? any 1-yes/0-no";
	    cin>>variant;
	while(variant)
		{
			cout<<"1)Ввести 1-ю дату";
			cout<<endl<<"2)Ввести 2-ю дату";
			cout<<endl<<"3)Прибавить к 1 дате число";
			cout<<endl<<"4)Прибавить ко 2 дате число";
			cout<<endl<<"5)Вывести 1 дату";
			cout<<endl<<"6)Вывести 2 дату";
			cout<<endl<<"7)Сравнить 2 даты";
			cout<<endl<<"8)Применить метод ++ к 1 дате";
			cout<<endl<<"9)Применить метод ++ к 2 дате";
			cout<<endl<<"10)Пункт отладки вывести количество дней 1 даты";
			cout<<endl<<"11)Пункт отладки вывести количество дней 2 даты";
			cout<<endl<<"12)Выход"<<endl;

			cin>>variant;
			switch(variant)
			{
			case 1:
			   cout<<"Первая дата"<<endl;
               cin>>date_of_something; 
               break;
			case 2:
			   cout<<"Вторая Дата"<<endl;
               cin>>date_of_something2;
               break;
			case 3:
			   cout<<"Введите число";
			   cin>>chislo;
			   date_of_something+=chislo;
			   break;
			case 4:
			   cout<<"Введите число";
			   cin>>chislo;
			   date_of_something2+=chislo;
			   break;
			case 5:
			   cout<<endl<<"Выводим 1 дату"<<date_of_something<<endl;
			   break;
			case 6:
			   cout<<endl<<"Выводим 2 дату"<<date_of_something2<<endl;
			   break;
			case 7:
			 if (date_of_something>date_of_something2) 
                cout<<endl<<"Выводим 1 дату"<<date_of_something<<endl; 
                  else
                     cout<<endl<<"Выводим 2 дату"<<date_of_something2<<endl;
             break;
			case 8:
			   date_of_something++;
			   break;
			case 9:
			   date_of_something2++;
			   break;
			case 10:
			   date_of_something.print_all_days_and_date();
			   break;
			case 11:
			   date_of_something2.print_all_days_and_date();
			   break;
			case 12:
			   variant=0;
			   break;
			default :
			   cout<<"Нет такой команды повторите ввод"<<endl;
			   break;
		    }
		}
	return 0;
}
