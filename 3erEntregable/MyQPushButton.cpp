#include"MyQPushButton.h"
#include <iostream>
#include<QString>
#include<QPalette>
#include<QColor>
MyQPushButton::MyQPushButton(QWidget *parent)
        : QPushButton(parent) {
            dialValueAnterior = 50;
        }





void MyQPushButton::tractaDial(int dialValue){
    if(dialValue == 65 or dialValue == 80 or dialValue == 99 or dialValue == 15 or dialValue == 35 or dialValue == 50){ // Apunta a groc
        if(dialValueAnterior < dialValue){//++60
            QColor color = QWidget::palette().color(QWidget::backgroundRole());
            std::string hue;
            if(color.hsvHue() == 0)
                 hue = std::to_string(300);
            else
                 hue = std::to_string(color.hsvHue()-60);

            std::string saturation = std::to_string(color.hsvSaturation());
            std::string brightness = std::to_string(color.value());
            std::string colorfonsnou = "hsv("+hue + ","+saturation+","+brightness+");";


            QColor colorlletra = QWidget::palette().color(QWidget::foregroundRole());
            std::string huelletra = hue;
            std::string saturationlletra = std::to_string(colorlletra.hsvSaturation());
            std::string brightnesslletra = std::to_string(colorlletra.value());
            std::string colorlletranou = "hsv("+huelletra + ","+saturationlletra+","+brightnesslletra+");";


            setStyleSheet("background-color:" + QString::fromUtf8(colorfonsnou.c_str()) + "color: " + QString::fromUtf8(colorlletranou.c_str()) );
            
        }
        if(dialValueAnterior > dialValue){
            QColor color = QWidget::palette().color(QWidget::backgroundRole());
            std::string hue;
            if(color.hsvHue() == 300)
                 hue = std::to_string(0);
            else
                 hue = std::to_string(color.hsvHue()+60);

            std::string saturation = std::to_string(color.hsvSaturation());
            std::string brightness = std::to_string(color.value());
            std::string colorfonsnou = "hsv("+hue + ","+saturation+","+brightness+");";

            QColor colorlletra = QWidget::palette().color(QWidget::foregroundRole());
            std::string huelletra = hue;
            std::string saturationlletra = std::to_string(colorlletra.hsvSaturation());
            std::string brightnesslletra = std::to_string(colorlletra.value());
            std::string colorlletranou = "hsv("+huelletra + ","+saturationlletra+","+brightnesslletra+");";


            setStyleSheet("background-color:" + QString::fromUtf8(colorfonsnou.c_str()) + "color: " + QString::fromUtf8(colorlletranou.c_str()) );
            
        }
        dialValueAnterior = dialValue;
        canviaText();
    }


}



void MyQPushButton::canviaText(){
    QColor color = QWidget::palette().color(QWidget::backgroundRole());
    if(color.hue() == 0)
        setText("red");
    else if(color.hue() == 60)
        setText("yellow");
    else if(color.hue() == 120)
        setText("green");
    else if(color.hue() == 180)
        setText("cyan");
    else if(color.hue() == 240)
        setText("blue");
    else if(color.hue() == 300)
        setText("magenta");
    
}



void MyQPushButton::canviaBrightness(int newB){
    QColor color = QWidget::palette().color(QWidget::backgroundRole());
    std::string hue = std::to_string(color.hsvHue());
    std::string saturation = std::to_string(color.hsvSaturation());
    std::string brightness = std::to_string(newB);
    std::string colorfonsnou = "hsv("+hue + ","+saturation+","+brightness+");";


    QColor colorlletra = QWidget::palette().color(QWidget::foregroundRole());
    std::string huelletra = std::to_string(colorlletra.hsvHue());
    std::string saturationlletra = std::to_string(colorlletra.hsvSaturation());
    std::string brightnesslletra;
    if(newB - 100 > 0)
         brightnesslletra = std::to_string(newB-100);
    else
         brightnesslletra = std::to_string(0);
    
    std::string colorlletranou = "hsv("+huelletra + ","+saturationlletra+","+brightnesslletra+");"; 
    setStyleSheet("background-color:" + QString::fromUtf8(colorfonsnou.c_str()) + "color: " + QString::fromUtf8(colorlletranou.c_str())  );
}
