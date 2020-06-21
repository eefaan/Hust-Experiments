/* problem: closest points */
#include<iostream>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

class POINT{
public:
    double x;
    double y;
    POINT(){}
    POINT(double x, double y){//make POINT
        POINT::x=x;
        POINT::y=y;
    }
};

//平面上点对距离
double mydistance(POINT a, POINT b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

//合并时比较δ距离
double min(double a, double b){
    return (a<b)?a:b;
}

//自定义排序规则：依照结构体中的x成员变量升序排序
bool compareX(POINT a, POINT b){
    return a.x < b.x;
}

//自定义排序规则：依照结构体中的x成员变量升序排序
bool compareY(POINT a, POINT b){
    return a.y < b.y;
}

//求出最近点对记录，并将两点记录再a、b中
double cal_mindistance(POINT points[], int length, POINT &a, POINT &b){
    double mindistance;                //记录集合points中最近两点距离
    double distance1, distance2, distance3;                     //记录分割后两个子集中各自最小点对距离
    int i = 0, j = 0, k = 0, x = 0;    //用于控制for循环的循环变量
    POINT a1, b1, a2, b2;              //保存分割后两个子集中最小点对

    if (length < 2) return 100000;    //若子集长度小于2，定义为最大距离，表示不可达

    else if (length == 2){//若子集长度等于2，直接返回该两点的距离
        a = points[0];
        b = points[1];
        return mydistance(points[0], points[1]);
    }

    else{//子集长度大于3，进行分治求解
        //分解
        POINT *pts1 = new POINT[length/2];     //开辟两个子集
        POINT *pts2 = new POINT[length-length/2];

        double mid = points[(length - 1) / 2].x;    //排完序后的中间下标值，即中位数

        for (i = 0; i < length / 2; i++)
            pts1[i] = points[i];
        for (int j = 0, i = length / 2; i < length; i++)
            pts2[j++] = points[i];

        distance1 = cal_mindistance(pts1, length / 2, a1, b1);             //分治求解左半部分子集的最近点
        distance2 = cal_mindistance(pts2, length - length / 2, a2, b2);    //分治求解右半部分子集的最近点

        if (distance1 < distance2) { mindistance = distance1; a = a1; b = b1; }            //记录最近点，最近距离
        else { mindistance = distance2; a = a2; b = b2; }

        //合并：求解跨分割线并在δ×2δ区间内的最近点对
        POINT *pts3 = new POINT[length];

        for (i = 0, k = 0; i < length; i++)                        //取得中线2δ宽度的所有点对共k个
            if (abs(points[i].x - mid) <= mindistance)
                pts3[k++] = points[i];

        sort(pts3, pts3 + k, compareY);                                       // 以y排序矩形阵内的点集合

        for (i = 0; i < k; i++)
        {
            for (j = i + 1; j <= i + 6 && j < k; j++)            //只需与有序的领接的的6个点进行比较
            {
                distance3 = mydistance(pts3[i], pts3[j]);
                if (distance3 < mindistance)
                {//如果跨分割线的两点距离小于已知最小距离，则记录该距离和两点
                    a = pts3[i];
                    b = pts3[j];
                    mindistance = distance3;
                }
            }
        }
        return mindistance;
    }
}

#define COORDINATE_RANGE 100
void SetPoints(POINT *points, int length)
{//随机函数对点数组points中的二维点进行初始化
    srand(unsigned(time(NULL)));
    double digital;
    for (int i = 0; i < length; i++)
    {
        digital = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
        digital /= 100;
        points[i].x = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
        points[i].x += digital;
        digital = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
        digital /= 100;
        points[i].y = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
        points[i].y += digital;
    }
}

int main(void)
{
    int num;            //随机生成的点对个数
    POINT a, b;            //最近点对
    double diatance;    //点对距离

    while(1){
        cout << "请输入二维点对个数:";
        cin >> num;
        if (num < 2)
            cout << "请输入两个以上点" << endl;
        else
        {
            cout << endl << "随机生成的" << num << "个二维点对如下：" << endl;
            POINT *points = new POINT[num];

            SetPoints(points, num);
            for (int i = 0; i < num; i++)
                cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

            sort(points, points + num, compareX);    //调用algorithm库中的sort函数对points进行排序，compareX为自定义的排序规则

            diatance = cal_mindistance(points, num, a, b);
            cout << endl << endl << "按横坐标排序后的点对:" << endl;
            for (int i = 0; i < num; i++)
                cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

            cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" << "(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;

            delete(points);
        }
        cout<<endl<<endl;
    }
}
