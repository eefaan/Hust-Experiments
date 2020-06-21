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

//ƽ���ϵ�Ծ���
double mydistance(POINT a, POINT b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

//�ϲ�ʱ�ȽϦľ���
double min(double a, double b){
    return (a<b)?a:b;
}

//�Զ�������������սṹ���е�x��Ա������������
bool compareX(POINT a, POINT b){
    return a.x < b.x;
}

//�Զ�������������սṹ���е�x��Ա������������
bool compareY(POINT a, POINT b){
    return a.y < b.y;
}

//��������Լ�¼�����������¼��a��b��
double cal_mindistance(POINT points[], int length, POINT &a, POINT &b){
    double mindistance;                //��¼����points������������
    double distance1, distance2, distance3;                     //��¼�ָ�������Ӽ��и�����С��Ծ���
    int i = 0, j = 0, k = 0, x = 0;    //���ڿ���forѭ����ѭ������
    POINT a1, b1, a2, b2;              //����ָ�������Ӽ�����С���

    if (length < 2) return 100000;    //���Ӽ�����С��2������Ϊ�����룬��ʾ���ɴ�

    else if (length == 2){//���Ӽ����ȵ���2��ֱ�ӷ��ظ�����ľ���
        a = points[0];
        b = points[1];
        return mydistance(points[0], points[1]);
    }

    else{//�Ӽ����ȴ���3�����з������
        //�ֽ�
        POINT *pts1 = new POINT[length/2];     //���������Ӽ�
        POINT *pts2 = new POINT[length-length/2];

        double mid = points[(length - 1) / 2].x;    //���������м��±�ֵ������λ��

        for (i = 0; i < length / 2; i++)
            pts1[i] = points[i];
        for (int j = 0, i = length / 2; i < length; i++)
            pts2[j++] = points[i];

        distance1 = cal_mindistance(pts1, length / 2, a1, b1);             //���������벿���Ӽ��������
        distance2 = cal_mindistance(pts2, length - length / 2, a2, b2);    //��������Ұ벿���Ӽ��������

        if (distance1 < distance2) { mindistance = distance1; a = a1; b = b1; }            //��¼����㣬�������
        else { mindistance = distance2; a = a2; b = b2; }

        //�ϲ�������ָ��߲��ڦġ�2�������ڵ�������
        POINT *pts3 = new POINT[length];

        for (i = 0, k = 0; i < length; i++)                        //ȡ������2�Ŀ�ȵ����е�Թ�k��
            if (abs(points[i].x - mid) <= mindistance)
                pts3[k++] = points[i];

        sort(pts3, pts3 + k, compareY);                                       // ��y����������ڵĵ㼯��

        for (i = 0; i < k; i++)
        {
            for (j = i + 1; j <= i + 6 && j < k; j++)            //ֻ�����������ӵĵ�6������бȽ�
            {
                distance3 = mydistance(pts3[i], pts3[j]);
                if (distance3 < mindistance)
                {//�����ָ��ߵ��������С����֪��С���룬���¼�þ��������
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
{//��������Ե�����points�еĶ�ά����г�ʼ��
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
    int num;            //������ɵĵ�Ը���
    POINT a, b;            //������
    double diatance;    //��Ծ���

    while(1){
        cout << "�������ά��Ը���:";
        cin >> num;
        if (num < 2)
            cout << "�������������ϵ�" << endl;
        else
        {
            cout << endl << "������ɵ�" << num << "����ά������£�" << endl;
            POINT *points = new POINT[num];

            SetPoints(points, num);
            for (int i = 0; i < num; i++)
                cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

            sort(points, points + num, compareX);    //����algorithm���е�sort������points��������compareXΪ�Զ�����������

            diatance = cal_mindistance(points, num, a, b);
            cout << endl << endl << "�������������ĵ��:" << endl;
            for (int i = 0; i < num; i++)
                cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

            cout << endl << "������Ϊ��" << "(" << a.x << "," << a.y << ")��" << "(" << b.x << "," << b.y << ")" << endl << "�����Ծ���Ϊ��" << diatance << endl;

            delete(points);
        }
        cout<<endl<<endl;
    }
}
