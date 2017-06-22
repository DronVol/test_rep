#include <iostream>
#include <queue>
#include <string> 
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream> 
#include <stdio.h>
#include <cstdlib>
 
using namespace std;

class Sort{
	public:
	Sort(size_t file_s, size_t read_s, size_t file_num_s, size_t mem_s){
		file_size = file_s
		read_size = read_s
		file_num_size = file_num_s
		mem_size = mem_s
		//batch_size = buf_len/(sort_number + 1);
	}
	
	~Sort(){
		del();
	};

	void del(){
		//по окончании работы удаляем временные файлы
		system("rm -rf tmp");
		cout << "tmp folder removed.\n";
	}

	void init(const char * INPUT_FILE){
		// Разбиваем наш большой файл на множество отсортированных размером >= buf_len
		system("mkdir tmp");

		ifstream FileIn(INPUT_FILE, ios:: in | ios::binary);				
		size_t num = 0;//номер текущего файла вывода
		size_t position = 0;//смещение в исходном файле

		while (file_size > position){
			FileIn.seekg(position);

			// количество байт, которые мы запишем в новый файл
			size_t l = mem_size;
			if(mem_size > file_size - position)
				l = file_size - position;

			// считываем батч
			vector<int> buf(l / sizeof(int));
			FileIn.read(reinterpret_cast<char*>(buf.data()), buf.size()*sizeof(int)); 

			//сортируем
			sort(buf.begin(), buf.end());

			//выводим в новый файл				
			stringstream  touch_file;
			touch_file <<  "tmp/init" << num;
			ofstream FileOut;
			FileOut.open(touch_file.str(), ios::out | ofstream::binary);
			FileOut.write(reinterpret_cast<const char*>(&buf[0]), buf.size() * sizeof(int));
			FileOut.close();
			position += l;
			num++;

			//добавляем новый файл в очередь
			FILES.push(touch_file.str());
		}
		FileIn.close();
	}

		void file_sort(){
			// сортировка множества файлов
			int num = 0; // номер нового файла после merge
			while (FILES.size() > 1){

				cout << "FILES LEFT: "<< FILES.size() << "\n";
				vector<string> files; // батч файлов для merge

				for (int i=0; (i<sort_number) && (i <= FILES.size()) ; ++i){//sort_number = file_num_size, в этом цикле выбираем из FILES столько файлов, сколько можем открыть на чтение
					files.push_back(FILES.front());
					FILES.pop();
				}

				merge(files, num);//<--- Основные демоны сидят тут.
				files.clear();
				
				stringstream  touch_file;
				touch_file <<  "tmp/new" << num;
				FILES.push(touch_file.str());
				num++;
			}

			// по окончании скопируем оставшийся "собранный" файл в качестве result
			stringstream  cmd;
			cmd <<  "cp " << FILES.front() << " result";
			const string tmp = cmd.str();
			const char* cstr = tmp.c_str();
			cout << cstr << "\n";
			system(cstr);
			
		}

	private:
		int buf_len; // размер буфера
		int sort_number; // количество файлов при сортировке
		int batch_size; // размер сортировочного батча
		queue<string> FILES; // очередь файлов
};


int main(int argc, char** argv)
{
	size_t KB = 1024 ;
	//в качестве параметров возьмём объём файла, объём считывания данных за раз с диска и максимальное число поддерживаемых файлов на открытие.
	//И ещё количество оперативной памяти. С этими параметрами будем создавато класс Sort
	size_t buf_size = (size_t) atoll(argv[3]) * KB;
	size_t sort_files = (size_t) atoll(argv[2]);

	char* INPUT_FILE//<--- возможно, следует определить в init() и передать после в main()
	INPUT_FILE = "to_sort"
	ifstream FileIn(INPUT_FILE, ios:: in | ios::binary);				
	FileIn.seekg(0, FileIn.end);
	size_t file_size = FileIn.tellg();
	FileIn.close();//<---

	Sort s(file_size, read_size, file_num_size, mem_size);
	s.init(argv[1]);
	s.file_sort();

    return 0;
}