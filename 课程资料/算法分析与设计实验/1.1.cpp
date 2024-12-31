#include<bits/stdc++.h>
using namespace std;
const double PI = 3.14159265;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    double x1,y1,r1,x2,y2,r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double dis = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    cout << fixed << setprecision(3);
    if(dis >= r1+r2)
        cout << "0.000\n";
    else if(dis <= fabs(r1-r2))
        cout << PI*pow(min(r1,r2),2) << '\n';
    else
    {
        double angle = acos((r1*r1+dis*dis-r2*r2)/(2*r1*dis));
        double s = angle*r1*r1 - 0.5*r1*r1*sin(2*angle);
        angle = acos((r2*r2+dis*dis-r1*r1)/(2*r2*dis));
        s += angle*r2*r2 - 0.5*r2*r2*sin(2*angle);
        cout << s << '\n';
    }
}
