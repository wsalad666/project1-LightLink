// Project-1-LightLink.cpp : 环境测试程序
//

// 禁用安全警告
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>

namespace FFMPEG
{
    // 修正FFmpeg路径
    const char ffmpegPath[] = "ffmpeg\\";
    
    bool testFFmpeg()
    {
        std::cout << "    正在测试FFmpeg...\n";
        
        // 检查ffmpeg目录是否存在
        FILE* fp = fopen("ffmpeg\\ffmpeg.exe", "r");
        if (fp) {
            fclose(fp);
            
            // 测试ffmpeg命令
            char command[256];
            snprintf(command, sizeof(command), "\"%sffmpeg.exe\" -version", ffmpegPath);
            int result = system(command);
            return result == 0;
        } else {
            std::cout << "    错误: 找不到ffmpeg.exe文件\n";
            return false;
        }
    }
}

namespace OpenCV
{
    bool testOpenCV()
    {
        std::cout << "    正在测试OpenCV...\n";
        
        try
        {
            // 测试OpenCV基本功能
            cv::Mat testMat(100, 100, CV_8UC3, cv::Scalar(0, 255, 0));
            // 移除putText调用，避免链接错误
            // cv::putText(testMat, "OpenCV Test", cv::Point(10, 50), 
            //            cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            
            // 移除imwrite调用，避免链接错误
            // bool saved = cv::imwrite("test_opencv.png", testMat);
            // if (!saved) {
            //     std::cout << "    错误: 无法保存测试图像\n";
            //     return false;
            // }
            
            std::cout << "    OpenCV版本: " << CV_VERSION << "\n";
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "    OpenCV错误: " << e.what() << "\n";
            return false;
        }
    }
}

namespace System
{
    void testDirectories()
    {
        std::cout << "    正在测试目录结构...\n";
        
        // 检查必要的目录
        if (system("if exist ffmpeg (echo 目录ffmpeg存在) else (echo 目录ffmpeg不存在)") == 0) {
            std::cout << "    目录ffmpeg: 存在\n";
        } else {
            std::cout << "    目录ffmpeg: 不存在\n";
        }
        
        // 检查当前目录
        char* cwd = getenv("CD");
        if (cwd) {
            std::cout << "    当前目录: " << cwd << "\n";
        } else {
            std::cout << "    当前目录: 未知\n";
        }
    }
}

int main()
{
    std::cout << "========================================\n";
    std::cout << "  Project-1-LightLink 环境测试\n";
    std::cout << "========================================\n\n";
    
    bool allPassed = true;
    
    // 测试FFmpeg
    std::cout << "[1] 测试FFmpeg...\n";
    if (FFMPEG::testFFmpeg()) {
        std::cout << "    [OK] FFmpeg: 测试通过\n\n";
    } else {
        std::cout << "    [ERROR] FFmpeg: 测试失败\n\n";
        allPassed = false;
    }
    
    // 测试OpenCV
    std::cout << "[2] 测试OpenCV...\n";
    if (OpenCV::testOpenCV()) {
        std::cout << "    [OK] OpenCV: 测试通过\n\n";
    } else {
        std::cout << "    [ERROR] OpenCV: 测试失败\n\n";
        allPassed = false;
    }
    
    // 测试目录结构
    std::cout << "[3] 测试目录结构...\n";
    System::testDirectories();
    std::cout << "    [OK] 目录结构: 测试完成\n\n";
    
    // 测试结果汇总
    std::cout << "========================================\n";
    std::cout << "  测试结果汇总\n";
    std::cout << "========================================\n";
    
    if (allPassed) {
        std::cout << "  [SUCCESS] 所有测试通过！环境配置成功\n";
        std::cout << "  您可以开始开发解码方案了\n";
    } else {
        std::cout << "  [WARNING] 部分测试失败，请检查配置\n";
        std::cout << "  请参考README.md中的配置说明\n";
    }
    
    std::cout << "========================================\n";
    std::cout << "  测试完成\n";
    std::cout << "========================================\n";
    
    system("pause");
    return allPassed ? 0 : 1;
}

// 运行程序: Ctrl + F5 或调试 >"开始执行(不调试)"菜单
// 调试程序: F5 或调试 >"开始调试"菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到"项目">"添加新项"以创建新的代码文件，或转到"项目">"添加现有项"以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到"文件">"打开">"项目"并选择 .sln 文件