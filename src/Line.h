#include <math.h>
#include <string>

class Line
{
public:
    Line(double p1[2], double p2[2]);
    Line(double m, double b);
    double solve(double x);
    double solve_x(double y);
    int crossed_by(double p[2]);
    double distance_to(double p[2]);
    bool intersection(Line l, double p[2]);
private:
    double p1[2];
    double p2[2];
    double m;
    double b;
    // to prevent recalculation:
    double p2_sub_p1[2];
    double p2_sub_p1_norm;
    // A, B, C coefficients of the line equation
    double A;
    double B;
    double C;
public:
    void get_points(double p1[2], double p2[2]);
    double get_m();
    double get_b();
    void get_p1(double p1[2]);
    void get_p2(double p2[2]);
    std::string to_string();
};

Line::Line(double p1[2], double p2[2])
{
    this->p1[0] = p1[0];
    this->p1[1] = p1[1];
    this->p2[0] = p2[0];
    this->p2[1] = p2[1];
    this->m = (p2[1] - p1[1]) / (p2[0] - p1[0]);
    this->b = p1[1] - m * p1[0];
    // to prevent recalculation:
    this->p2_sub_p1[0] = p2[0] - p1[0];
    this->p2_sub_p1[1] = p2[1] - p1[1];
    this->p2_sub_p1_norm = sqrt(p2_sub_p1[0] * p2_sub_p1[0] + p2_sub_p1[1] * p2_sub_p1[1]);
    // A, B, C coefficients of the line equation
    this->A = (p1[1] - p2[1]);
    this->B = (p2[0] - p1[0]);
    this->C = -(p1[0]*p2[1] - p2[0]*p1[1]);
}

Line::Line(double m, double b)
{
    // produce two points on the line
    this->p1[0] = 0;
    this->p1[1] = b;
    this->p2[0] = 10;
    this->p2[1] = m * 10 + b;
    this->m = m;
    this->b = b;
    // to prevent recalculation:
    this->p2_sub_p1[0] = p2[0] - p1[0];
    this->p2_sub_p1[1] = p2[1] - p1[1];
    this->p2_sub_p1_norm = sqrt(p2_sub_p1[0] * p2_sub_p1[0] + p2_sub_p1[1] * p2_sub_p1[1]);
    // A, B, C coefficients of the line equation
    this->A = (p1[1] - p2[1]);
    this->B = (p2[0] - p1[0]);
    this->C = -(p1[0]*p2[1] - p2[0]*p1[1]);
}

double Line::solve(double x)
{
    return m * x + b;
}

double Line::solve_x(double y)
{
    return (y - b) / m;
}

int Line::crossed_by(double p[2])
{
    double v1[2] = {this->p2_sub_p1[0], this->p2_sub_p1[1]};
    double v2[2] = {this->p2[0] - p[0], this->p2[1] - p[1]};
    double xp = v1[0] * v2[1] - v1[1] * v2[0];
    if (xp > 0)
    {
        return -1;
    }
    if (xp < 0)
    {
        return 1;
    }
    return 0; // on the line
}

double Line::distance_to(double p[2])
{
    double cross_product = fabs((p2_sub_p1[0] * (p1[1] - p[1])) - ((p1[0] - p[0]) * p2_sub_p1[1]));
    return cross_product / p2_sub_p1_norm;
}

bool Line::intersection(Line l, double p[2])
{
    double D = A * l.B - B * l.A;
    if (D == 0)
    {
        return false;
    }
    p[0] = (C * l.B - B * l.C) / D;
    p[1] = (A * l.C - C * l.A) / D;
    return true;
}

void Line::get_points(double p1[2], double p2[2])
{
    p1[0] = this->p1[0];
    p1[1] = this->p1[1];
    p2[0] = this->p2[0];
    p2[1] = this->p2[1];
}

double Line::get_m()
{
    return this->m;
}

double Line::get_b()
{
    return this->b;
}

void Line::get_p1(double p1[2])
{
    p1[0] = this->p1[0];
    p1[1] = this->p1[1];
}

void Line::get_p2(double p2[2])
{
    p2[0] = this->p2[0];
    p2[1] = this->p2[1];
}

std::string Line::to_string()
{
    std::string s = "Line: ";
    s += std::to_string(this->p1[0]) + " " + std::to_string(this->p1[1]) + " " + std::to_string(this->p2[0]) + " " + std::to_string(this->p2[1]);
    s += " m: " + std::to_string(this->m) + " b: " + std::to_string(this->b);
    return s;
}