#ifndef Modelo_h
#define Modelo_h

#pragma once
#include <string>
#include "Complejo.h"
#include <math.h>
#include <stdio.h>

// La clase Modelo permite recrear la respuesta de un sistema LTI de hasta 
// 2 ceros y 2 polos ante una entrada escalon u(t) de amplitud K
// Y(S)=k·(tZ1·s+1)·(tZ2·s+1)
//        ---------------
//        (tP1·s+1)·(tP2·s+1)

// Y(S)=        k
//        -------------   Subamortiguado
  //        (a·s²+b·s+c)

class Modelo
{
public:
    Modelo(const std::string& name,float _tZ1,float _tZ2,float _tP1,float _tP2,float _k,float _c0);
    Modelo(const std::string& name,Complejo *_raiz,float _k,float _c0);//Sistema Subamortiguado
    Modelo(const Modelo& );
    virtual ~Modelo();
    void Update(float t);//Calcular salida del sistema LTI y(t)
    float GetValue();//Acceso al valor de salida y(t) del sistema LTI
    const std::string GetName();//Acceso al nombre del modelo
    bool GetPermanente();//Acceso al estado permanente del sistem LTI
    void StartModelo(float ,float ,float);//Inicia el sistema LTI
    void StopModelo();//Desconecta el sistema LTI
    bool ModeloStarted();//Acceso al estado ON/OFF del sistema LTI
    float GetK(){return k;}//Retorno valor
    void SetC0(float _c0){c0=_c0;}//Seteo condiciones iniciales  		             ______
    bool Check_K(float ,float );//Comprueba cambios en la señal de consigna K __|
    void SetValue(float v){aux_k=value=v;}// Fuerza el valor del modelo
    void SetCoef(float _tZ1,float _tZ2,float _tP1,float _tP2); 
     
private:
    const std::string m_name;//Nombre del instrumento
    float k,aux_k;//Amplitud de la señal de consigna Escalon
    float tZ1,tZ2,tP1,tP2;//Constantes del sistema LTI Y(S)
    float c1,c2,c3,c4;//Constantes del sistema LTI y(t)
    float c0;//Condicion inicial
    bool subamortiguado;//Polos complejos
    Complejo raiz;//Complejo raiz del sistem LTY Y(S) subamortiguado
    float c5;//Constantes del sistema LTI y(t) subamortiguado
    float t0,t;// Tiempo del sistema LTI y(t)
    bool state;//Estado ON/OFF del sistema LTI
    float value;//Salida del sistema y(t)
    bool permanente;//Estado permanente del sistema LTI
};
#endif
