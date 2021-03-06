#include "zealot_predefine.h"
#include "zealot_test_function.h"


int test_osadapt_file(int  /*argc*/, char * /*argv*/[])
{
#if defined ZCE_OS_WINDOWS

    int file_desc = open("C:\\123.txt", O_CREAT | O_APPEND);

    if (file_desc == 0)
    {
        return 0;
    }

    //fh_1 == fh_2 内核句柄一致
    HANDLE fh_1 = (HANDLE)_get_osfhandle(file_desc);
    HANDLE fh_2 = (HANDLE)_get_osfhandle(file_desc);


    std::cout << (int) fh_1 << std::endl;
    std::cout << (int) fh_2 << std::endl;

    //file_desc != filedesc_1 != filedesc_2,3个文件描述符不一样
    int filedesc_1 = _open_osfhandle((intptr_t)fh_1, O_RDONLY);
    int filedesc_2 = _open_osfhandle((intptr_t)fh_1, O_RDONLY);

    std::cout << (int) filedesc_1 << std::endl;
    std::cout << (int) filedesc_2 << std::endl;

    //fh_1 == fh_2 == fh_3,内核句柄一致一致
    HANDLE fh_3 = (HANDLE)_get_osfhandle(filedesc_1);
    std::cout << (int) fh_3 << std::endl;

#endif

    return 0;
}

int test_osadapt_perf(int  /*argc*/, char * /*argv*/[])
{
    int ret = 0;
    ZCE_PROCESS_PERFORM prc_perf_info;
    ret = ZCE_LIB::get_self_perf(&prc_perf_info);

    if (ret != 0)
    {
        return ret;
    }

    ZCE_SYSTEM_INFO zce_system_info;
    ret = ZCE_LIB::get_system_info(&zce_system_info);

    if (ret != 0)
    {
        return ret;
    }

    ZCE_SYSTEM_PERFORMANCE zce_system_perf;
    ret =  ZCE_LIB::get_system_perf(&zce_system_perf);

    if (ret != 0)
    {
        return ret;
    }


    return 0;
}




#include "zealot_predefine.h"
#include "zealot_test_function.h"

//选取所有的.h文件
int hfile_selector(const struct dirent *dir_info)
{
    size_t name_len = strlen (dir_info->d_name);
    if (name_len <= 2)
    {
        return 0;
    }
    if ((dir_info->d_name[name_len - 1] == 'h' || dir_info->d_name[name_len - 1] == 'H')
        && dir_info->d_name[name_len - 2] == '.')
    {
        return 1;
    }
    return 0;
}

int test_scandir(int /*argc*/, char /*argv*/ *[])
{
    ZCE_LIB::clear_last_error();
    struct  dirent  **namelist = NULL;
    int number_file =  ZCE_LIB::scandir("E:\\Courage\\readline-5.2",
                                       &namelist,
                                       hfile_selector,
                                       ZCE_LIB::scandir_namesort);

    if (number_file <= 0)
    {
        std::cout << "error." << std::endl;
        return -1;
    }

    for (int i = 0; i < number_file; i++)
    {
        std::cout << "file name " << i << ":" << namelist[i]->d_name << std::endl;
    }


    ZCE_LIB::free_scandir_result(number_file, namelist);

    //for (int i = 0; i < number_file; ++i)
    //{
    //    ::free (namelist[i]);
    //}
    //::free (namelist);

    return 0;
}


struct Zealot_SVC :public ZCE_Server_Base
{

};

Zealot_SVC svc;
int test_pid_file(int /*argc*/, char /*argv*/ *[])
{
    svc.out_pid_file("C:\\1");
    return 0;
}


const size_t TEST_NUMBER = 100000 * 10;

void test_findwith_container(size_t container_len)
{

    std::vector<int>          int_vector;
    std::map<int, int>         int_map;
    unordered_map<int, int>    int_hash;

    int_vector.resize(container_len);
    int_hash.rehash(container_len);

    //
    for (size_t i = 0; i < container_len; i++)
    {
        int_vector[i] = (int)i;
        int_map[(int)i] = (int)i;
        int_hash[(int)i] = (int)i;

    }

    ZCE_HR_Progress_Timer test_timer;

    test_timer.restart();
    for (size_t i = 0; i < TEST_NUMBER; ++i)
    {

        int find_number =(int) i%container_len;
        //
        for (size_t j = 0; j < container_len; j++)
        {

            if (int_vector[j] == find_number)
            {
                break;
            }
        }
    }

    test_timer.end();
   

    std::cout << "test vector gettimeofday :" << test_timer.elapsed_usec() << " " << std::endl;

    test_timer.restart();
    for (size_t i = 0; i < TEST_NUMBER; ++i)
    {

        int find_number = (int)i%container_len;
        int_map.find(find_number);
    }

    test_timer.end();

    std::cout << "test map gettimeofday :" << test_timer.elapsed_usec() << " " << std::endl;


    test_timer.restart();
    for (size_t i = 0; i < TEST_NUMBER; ++i)
    {
        int find_number = (int)i%container_len;
        int_hash.find(find_number);
    }

    test_timer.end();


    std::cout << "test hash gettimeofday :" << test_timer.elapsed_usec() << " " << std::endl;

}



//

int test_container_performance(int  /*argc*/, char * /*argv*/[])
{

    for (int j = 0; j < 3; ++j)
    {

        std::cout << "container length = 10 " << std::endl;
        test_findwith_container(10);

        std::cout << "container length = 20 " << std::endl;
        test_findwith_container(20);

        std::cout << "container length = 50 " << std::endl;
        test_findwith_container(50);

        std::cout << "container length = 100 " << std::endl;
        test_findwith_container(100);

        std::cout << "container length = 200 " << std::endl;
        test_findwith_container(200);

        std::cout << "container length = 500 " << std::endl;
        test_findwith_container(500);

        std::cout << "container length = 1000 " << std::endl;
        test_findwith_container(1000);

    }

    return 0;
}
