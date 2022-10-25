//---------------------------------------- onnx的dnn推理-----------------------------------------
#include <iostream>
#include<windows.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;



HBITMAP	BitMap, hOld;
Mat img, img0, blob;     //img0是用来存储Bit位图的,不能占用,否者图片一直会叠加.img是bit转换出来的,blod是用来计算的



int main(int argc, char** argv)
{
    //截取原点宽高
    int x = 0;
    int y = 0;
    int width = 640;
    int height = 640;


    //1.获取屏幕句柄
    HWND hwnd = GetDesktopWindow();
    //2.获取屏幕DC
    HDC hdc = GetWindowDC(hwnd);
    //3.创建兼容DC(内存DC)
    HDC	mfdc = CreateCompatibleDC(hdc);
    //5.创建位图Bitmap对象
    BitMap = CreateCompatibleBitmap(hdc, width, height);
    //6.将位图对象放入内存dc(也可以是绑定)
    SelectObject(mfdc, BitMap);
    //7.创建一个固定维度的空矩阵,
    img0.create(Size(width, height), CV_8UC4);
    while (true)
    {

        //截图
        BitBlt(mfdc, 0, 0, width, height, hdc, x, y, SRCCOPY);
        //将BitBlt的位图信息传入
        GetBitmapBits(BitMap, height * width * 4, img0.data);//位图对象句柄,字节数,需要拷贝到的地方
        cvtColor(img0, img, COLOR_BGRA2BGR);  // 4->3,img0是转换后的图片,用来做输入


        auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        imshow("test", img);
        waitKey(100);

        cout << (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - tt) * 1000 << "ms" << endl;
    }
    //释放对象
    DeleteDC(hdc);
    DeleteDC(mfdc);
    DeleteObject(BitMap);
    return 0;
}
