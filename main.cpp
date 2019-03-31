#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>



int getdir (std::string dir, std::vector<std::string> &files, std::vector <int> &fileTypes)
{
    DIR *dp;
    struct dirent *dirp;
    
    if((dp  = opendir(dir.c_str())) == NULL) 
    {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) 
    {
        files.push_back(std::string(dirp->d_name));
        fileTypes.push_back(dirp->d_type);
        
    }
    closedir(dp);
    return 0;
}

int main()
{
    std::string dir = std::string("/sys/bus/w1/devices/");
    std::string dir2;
    std::vector <std::string> files = std::vector<std::string>();
    std::vector <int> fileTypes;
    std::ifstream inputFile;
    std::string line;
    
    getdir(dir,files, fileTypes);

        
    
    
    
    for (int i = 0;i < files.size();i++) 
    {
        if((fileTypes[i]!=DT_DIR)&&(fileTypes[i]!=DT_LNK))
        {
            fileTypes.erase(fileTypes.begin()+i);
            files.erase(files.begin()+i);
            i--;
        }

        
        if((files[i]==".")||(files[i]==".."))
        {
            files.erase(files.begin()+i);
            fileTypes.erase(fileTypes.begin()+i);
            i--;
        } 
        
    }
    
    for (int i = 0;i < files.size();i++) 
    {
        if(files[i].substr(0,2)!="28")
        {
            fileTypes.erase(fileTypes.begin()+i);
            files.erase(files.begin()+i);
            i--;
        }

        
        
    }
    

    
    for(int i=0;i<files.size();i++)
    {
        files[i].append("/w1_slave");
        files[i]=dir+files[i];
        
    }

   

    for(int i =0; i< files.size(); i++)
    {
            std::cout<<"Data from sensor "<<files[i]<<" is \n";
            inputFile.open(files[i], std::ios::in);
            while ( getline (inputFile,line) )
                {
                    std::cout << line << '\n';
                }
            inputFile.close();
            
            std::cout << "\n";

    }
    
    return 0;
    
    
}
