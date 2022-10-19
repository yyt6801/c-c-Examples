#include "ALARM.h"
/*
获得当前时间字符串
@param buffer [out]: 时间字符串
@return 空
*/
void get_local_time(char* buffer)
{
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
    (timeinfo->tm_year+1900), timeinfo->tm_mon + 1, timeinfo->tm_mday,
    timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

void get_local_date(char* buffer)
{
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(buffer, "%04d-%02d-%02d",
    (timeinfo->tm_year+1900), timeinfo->tm_mon + 1, timeinfo->tm_mday);
}
/*
获得文件大小
@param filename [in]: 文件名
@return 文件大小
*/
long get_file_size(char* filename)
{
    long length = 0;
    FILE *fp = NULL;
    fp = fopen(filename, "rb");
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    return length;
}
/*
写入日志文件
@param filename [in]: 日志文件名
@param max_size [in]: 日志文件大小限制
@param buffer [in]: 日志内容
@param buf_size [in]: 日志内容大小
@return 空
*/
void write_log_file(char* filename,long max_size, char* buffer, unsigned buf_size)
{
    if (filename != NULL && buffer != NULL)
    {
        // 文件超过最大限制, 删除
        long length = get_file_size(filename);
        if (length > max_size)
        {
            _unlink(filename); // 删除文件
        }
        // 写日志
        {
            FILE *fp;
            fp = fopen(filename, "at+");
            if (fp != NULL)
            {
                char now[32];
                memset(now, 0, sizeof(now));
                get_local_time(now);
                strcat(now," ");
                fwrite(now, strlen(now), 1, fp);
                fwrite(buffer, buf_size, 1, fp);
                fprintf(fp,"\n");//每条写完后自动换行
                fclose(fp);
                fp = NULL;
            }
        }
    }
}
void ALARM(int alarm_class, int alarm_num,char* buffer)
{
	char* dir = (char*)"log";
	if (_access(dir, 0) == -1)
	{
		printf("%s is not existing! now make it", dir);
#ifdef WIN32
		int flag = _mkdir(dir);
#endif
#ifdef linux 
		int flag = mkdir(dir, 0777);
#endif
		if (flag == 0)
		{
			printf("make it\n");
		}
		else {
			printf("make error\n");
		}
	}
    char today_date[32];
    memset(today_date, 0, sizeof(today_date));
    get_local_date(today_date);//.txt以日期命名
    char filename[32];
    memset(filename, 0, sizeof(filename));//.txt的日志名，每天一个
	strcpy(filename, ".\\log\\");
	strcat(filename, today_date);
    strcat(filename,".txt");

    write_log_file(filename, FILE_MAX_SIZE, buffer, strlen(buffer));

}