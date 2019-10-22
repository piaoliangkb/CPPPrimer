#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

// 主转换函数，调用 transformer
// 接受两个参数，第一个参数是映射规则的文件输入，第二个参数是要转换的段落输入
void word_transformer(std::fstream& mapfile, std::fstream& input);

// 接受一个映射规则的文件流，读取映射规则
// 返回一个映射的 map table
std::map<std::string, std::string> buildmap(std::fstream &mapfile);

// 转换函数
const std::string& transformer(const std::string& s, const std::map<std::string, std::string> &map);

std::map<std::string, std::string> buildmap(std::fstream& mapfile)
{
    std::string key;
    std::string value;
    std::map<std::string, std::string> map_table;
    while ((mapfile>>key) && (getline(mapfile, value)))
    {
        map_table[key] = value.substr(1).substr(0, value.find_last_not_of(' '));
    }

    return map_table;
}

const std::string& transformer(const std::string& s, const std::map<std::string, std::string>& map)
{
    auto iter = map.find(s);
    if (iter != map.end()) return iter->second;
    return s;
}

void word_transformer(std::fstream& mapfile, std::fstream& input)
{
    auto map_table = buildmap(mapfile);
    std::string text;
    while (getline(input, text))
    {
        std::istringstream iss(text);
        std::string word;
        while (iss >> word) {
            std::cout << transformer(word, map_table) << " ";
        }
        std::cout << std::endl;
    }

}

int main()
{
    std::fstream mapfile("map_rules_11_33.txt");
    std::fstream sourcetext("convert_source_11_33.txt");

    if (mapfile && sourcetext)
        word_transformer(mapfile, sourcetext);
    else
        std::cout << "cant find file of map_rules or source_text" << std::endl;
    return 0;
}   

