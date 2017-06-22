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
		public:
		Sort(size_t file_size, size_t read_size, size_t file_num_size, size_t mem_size){
			buf_len = buf_size;
			sort_number = sort_num;		
			batch_size = buf_len/(sort_number + 1);
		}
		
		~Sort(){
			del();
		};
}

int main(int argc, char** argv)
{
	size_t KB = 1024 ;
	//в качестве параметров возьмём объём файла, объём считывания данных за раз с диска и максимальное число поддерживаемых файлов на открытие. И ещё количество оперативной памяти. С этими параметрами будем создавато класс Sort
	size_t buf_size = (size_t) atoll(argv[3]) * KB; 
	size_t sort_files = (size_t) atoll(argv[2]); 

	Sort s(file_size, read_size, file_num_size, mem_size);
	s.init(argv[1]);
	s.file_sort();

    return 0;
}