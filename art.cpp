#include <iostream>
#include <fstream>
#include <vector>


class Canvas
{
    public:
        int width;
        int length;
        
    public:
        Canvas(int l, int w): width(w), length(l)
        {
            //std::cout << __PRETTY_FUNCTION__ << std::endl;
        };
        virtual ~Canvas() 
        {
            //std::cout << __PRETTY_FUNCTION__ << std::endl;
        };

        char **painting{nullptr};
};

class ASCIICanvas: public Canvas
{
    public:
        ASCIICanvas(int w, int l): Canvas(w, l)
        {
            painting = new char*[width+2];
            for(int i = 0; i < width+2; i++)
            {
                painting[i] = new char[length];
            }

            for(int i = 0; i < width+2; i++)
            {
                for(int j = 0; j < length+2; j++)
                {
                    if((i == 0 || i == width+1))
                    {
                        painting[i][j] = '=';
                    }
                    else if((j == 0 || j == length+1) && i != 0 && i != width+1)
                    {
                        painting[i][j] = '|'; 
                    }
                    else
                    {
                        painting[i][j] = ' ';
                    }
                }
            }
            //std::cout << __PRETTY_FUNCTION__ << std::endl;
        };

        ~ASCIICanvas() 
        {
            for(int i = 0; i < width+2; i++)
            {
                delete [] painting[i];
            }
            delete [] painting;
            //std::cout << __PRETTY_FUNCTION__ << std::endl;
        };

        void CPrint()
        {
            for(int i = 0; i < width+2; i++)
            {
                for(int j = 0; j < length+2; j++)
                {
                    std::cout << painting[i][j];
                }
                std::cout << std::endl;
            }
            //std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        void FPrint(std::string filename)
        {
            std::ofstream file(filename);
            for(int i = 0; i < width+2; i++)
            {
                for(int j = 0; j < length+2; j++)
                {
                    file << painting[i][j];
                }
                file << std::endl;
            }
        }
};

struct Point
{
    int x{0}, y{0};
    Point() { };
    Point(int X, int Y): x(X), y(Y) { };
};

class Figure
{
    protected:
        Point P;
        int len;
        int wid;
        char sym;
    public:
        Figure(): P(0, 0), len(0), wid(0), sym(' ')
        {

        };
        Figure(Point p, int l, int w, char s): P(p), len(l), wid(w), sym(s)
        {

        };
        virtual void Draw(Canvas &s) = 0;
        virtual void Set(Point pnt, int le, int wi, char sy) = 0;
        virtual ~Figure() { };
};

class Rectangle: public Figure
{
    public:
        Rectangle(): Figure()
        {

        };
        Rectangle(Point p, int l, int w, char s): Figure(p, l, w, s)
        {

        };
        ~Rectangle() { };
        void Draw(Canvas &s) override
        {
            for(int x = P.x; x < P.x + len; x++)
            {
                for(int y = P.y; y < P.y + wid; y++)
                {
                    s.painting[x][y] = sym;
                }
            }
        }
        void Set(Point pnt, int le, int wi, char sy) override
        {
            P = pnt;
            len = le;
            wid = wi;
            sym = sy;
        }
};

class Square: public Rectangle
{
    public:
        Square(): Rectangle()
        {

        };
        Square(Point p, int l, char s): Rectangle(p, l, l, s)
        {

        };
        void Set(Point pnt, int le, int, char sy) override
        {
            P = pnt;
            len = le;
            wid = le;
            sym = sy;
        }

        ~Square() { };
};

class Circle: public Figure
{
    public:
        Circle(): Figure()
        {

        };
        Circle(Point P, int R, char s): Figure(P, R, 0, s)
        {

        };
        void Draw(Canvas &s) override
        {
            //std::cout << P.x << " " << P.y << std::endl;
            for(int x = 1; x < s.width; x++)
            {
                for(int y = 1; y < s.length; y++)
                {
                    int uno = x - P.x;
                    int dos = y - P.y;
                    //std::cout << pow(uno, 2) + pow(dos, 2) << " " << x << " " << y << " " << ((pow(uno, 2) + pow(dos, 2) <= pow(len, 2)) ? pow(len, 2) : 0) << std::endl;
                    if(pow(uno, 2) + pow(dos, 2) <= (pow(len, 2)))
                    {
                        s.painting[x][y] = sym;
                    }
                }
            }

        }
        void Set(Point pnt, int r, int, char sy) override
        {
            P = pnt;
            len = r;
            wid = 0;
            sym = sy;
        }
        ~Circle() { };
};

int main(int argc, char* argv[])
{
    std::string filename(argv[1]);
    std::fstream INFILE;
    INFILE.open(filename);
    std::string temp;
    char* tempC;
    std::vector<std::string> cfg; 
    while(INFILE >> temp)
    {
        cfg.push_back(temp);
    }

    int canWid, canLen;
    char dummy1, d2, d3, d4;
    sscanf(cfg[1].c_str(), "%d%c%d", &canLen, &dummy1, &canWid);
    ASCIICanvas can1(canWid, canLen);

    std::string big;
    std::string where;
    char symbol;
    int w, l, x, y;
    
    Square SQ; Point SQPoint;
    Rectangle REC; Point RECPoint;
    Circle CIR; Point CIRPoint;

    for(int i = 2; i < cfg.size(); i+=4)
    {
        switch(cfg[i][0])
        {
            case 'R':
                big = cfg[i+1];
                sscanf(big.c_str(), "%d%c%d", &w, &dummy1, &l);

                where = cfg[i+2];
                sscanf(where.c_str(), "%c%d%c%d%c", &d2, &x, &d3, &y, &d4);

                symbol = cfg[i+3][0];

                RECPoint.x = x; RECPoint.y = y;
                REC.Set(RECPoint, l, w, symbol);
                REC.Draw(can1);
                break;

            case 'S':
                big = cfg[i+1];
                sscanf(big.c_str(), "%d%c%d", &w, &dummy1, &l);

                where = cfg[i+2];
                sscanf(where.c_str(), "%c%d%c%d%c", &d2, &x, &d3, &y, &d4);

                symbol = cfg[i+3][0];

                SQPoint.x = x; SQPoint.y = y;
                SQ.Set(SQPoint, l, w, symbol);
                SQ.Draw(can1);
                break;

            case 'C':
                big = cfg[i+1];
                w = stoi(big);

                where = cfg[i+2];
                sscanf(where.c_str(), "%c%d%c%d%c", &d2, &x, &d3, &y, &d4);

                symbol = cfg[i+3][0];

                CIRPoint.x = x; CIRPoint.y = y;
                CIR.Set(CIRPoint, w, w, symbol);
                CIR.Draw(can1);
                break;
        }
    }
    
    can1.FPrint(cfg[0]);
    can1.CPrint();
}