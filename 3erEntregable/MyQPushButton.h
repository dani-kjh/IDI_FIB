#include <QPushButton>

class MyQPushButton: public QPushButton
{
    Q_OBJECT
    public:
        MyQPushButton (QWidget *parent);
        int dialValueAnterior;
        void canviaText();
    public slots:
        void canviaBrightness(int newB);
        void tractaDial(int dialValue);
        
        signals:
            void enviaValors(int);
};