/*
	1.列出当前文件夹下所有的jpg文件
	2.找出步骤1中文件名是数字的文件
	3.找出步骤2中最大的数字
	
	参数1：目录，比如"/home/jason/图片/"
	参数2：图像类型，比如jpg
*/
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	DIR *dir;
	
	struct dirent *ent;
	
	std::string path = std::string(argv[1]); 
	
//	std::vector<std::string> filelist;
	int max_iiq_number = 0;
	
	//找到文件夹目录下jpg图像的最大数字文件名
	if ((dir = opendir (path.c_str())) != NULL) {
	  	/* print all the files and directories within directory */
	  	while ((ent = readdir (dir)) != NULL) {

			std::string filename = std::string(ent->d_name);
//	    	printf ("%s\n", filename.c_str());

			int dot_index = filename.find_last_of(".");
			int fn_len = filename.length();

			if (((fn_len - dot_index -1) == 3)) {   //缩小范围:后缀名长度必须为3

				std::string extension = filename.substr(filename.find_last_of(".") + 1);
				std::string filename_wo_ext = filename.erase(filename.find_last_of("."),4);
				//std::cout << filename.c_str() << "后缀名是" << extension.c_str() << std::endl;
				//std::cout << "fn_len is :" << fn_len << std::endl;
				//std::cout << "dot_index is :" << dot_index << std::endl;
				
				if ((strcmp(extension.c_str(),argv[2]) ==0) && \
				(!filename_wo_ext.empty() && filename_wo_ext.find_first_not_of("0123456789") == std::string::npos))   //缩小范围:后缀名必须为IIQ
				{
					int number = atoi (filename_wo_ext.c_str());
					max_iiq_number = (max_iiq_number < number)? number : max_iiq_number;
					std::cout << filename_wo_ext.c_str() << std::endl;
				}
			}
		}
		printf ("最大的%s文件名称为:%i \n", argv[2],max_iiq_number); 
	  	closedir (dir);
	} else {
	  	/* could not open directory */
	  	perror ("打不开图像目录 \n");
	  	return -1;
	}
	
}
