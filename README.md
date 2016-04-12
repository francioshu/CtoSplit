# CtoSplit
Code merge
字符串分割函数，可以根据提供的分隔符串列表将指定的字符串分割为若干个字符串，分隔符可以是单个字符也可以是字符串，可以设定是否压缩分隔符串（即当两个或者两个以上分隔符串连续出现时不生成空串），也可以设定是否把查找到的分隔符串也插入到结果中。需要注意的是结果是动态分配的内存，使用完毕后需要自己释放。详情请看函数头部注释，代码中有使用的示例。 
在 gcc 和 vs2008 下均通过测试 
接口： 
int strsplit(char ***dest, int *count, char *s_str, char **separator, int number_separators, int compress_separator, int keep_separator); 
参数说明： 
@Param dest     输出参数，保存字符串分割的结果，是指向字符串数组的指针，采用了动态内存分配，使用完毕需自己释放。 
@Param count    输出参数，保存成功被分割出的字符串个数。 
@Param s_str     输入参数，需要被分割的源字符串。 
@Param separator    输入参数，字符串数组，分割用的分隔符串列表 
@Param number_separator  输入参数，分隔符的个数 
@Param compress_separator 输入参数，是否压缩分隔符，即当源串中连续出现两个或者两个以上的分隔符时不生成中间的空串。 
@Param keep_separator 输入参数，是否把源串中查找到的分隔符也作为一个字符串存入结果中。
