#include "Modelo.h"

/**
* @brief 
* @param 
*/
Modelo::Modelo(const std::string& name,float _tZ1,float _tZ2,float _tP1,float _tP2,float _k,float _c0):m_name(name),raiz(0,0)
{
    tZ1=_tZ1;
    tZ2=_tZ2;
    tP1=_tP1;
    tP2=_tP2;
    k=_k;
    c0=_c0;
    aux_k=0;
    state=permanente=false;
    t0=value=0;
    subamortiguado=false;
    
    SetCoef(_tZ1,_tZ2,_tP1,_tP2);
}

/**
* @brief 
* @param 
*/
Modelo::Modelo(const std::string& name,Complejo *_raiz,float _k,float _c0):m_name(name),raiz(*_raiz)
{
    k=_k;
    aux_k=0;
    c0=_c0;
    state=permanente=false;
    t0=value=0;
    subamortiguado=true;

    c5=1/(sqrt(1-cos(raiz.theta)*cos(raiz.theta)));

    delete _raiz;
    tZ1=tZ2=tP1=tP2=c1=c2=c3=c4=0;
}

/**
* @brief 
* @param 
*/
Modelo::Modelo(const Modelo &m):m_name(m.m_name),tZ1(m.tZ1),tZ2(m.tZ2)
,tP1(m.tP1),tP2(m.tP2),k(m.k),c0(m.c0),c1(m.c1),c2(m.c2),c3(m.c3),c4(m.c4),state(m.state),
permanente(m.permanente),t0(m.t0),value(m.value),c5(m.c5),raiz(m.raiz),
subamortiguado(m.subamortiguado){}

/**
* @brief 
* @param 
*/
Modelo::~Modelo()
{

}

/**
* @brief 
* @param 
*/
void Modelo::SetCoef(float _tZ1,float _tZ2,float _tP1,float _tP2)
{
    tZ1=_tZ1;
    tZ2=_tZ2;
    tP1=_tP1;
    tP2=_tP2;

    if(tP1!=0)
    {
         //Constantes ecuacion temporal
        c1=(-tZ1*tZ2+tZ1*tP1+tZ2*tP1-tP1*tP1)/(tP1*(tP1-tP2));
        c2=(-1/tP1);
    }
    else
    {
        c1=c2=0;
    }

    if(tP2!=0)
    {
        //Constantes ecuacion temporal
        c3=(tZ1*tZ2-tZ1*tP2-tZ2*tP2+tP2*tP2)/(tP2*(tP1-tP2));
        c4=(-1/tP2);
    }
    else
    {
        c3=c4=0;
    }

	c5=0;
}

/**
* @brief 
* @param 
*/
void Modelo::Update(float _t)
{
    if(state)
    {
    	//t[seg]=tiempo run simulator-tiempo inicio arranque
    	t=(_t-t0);

        if(t<=0) return;

			//y(t)=L^-1[Y(s)]
    		if(!subamortiguado)
    		{
    			value=(k-aux_k)*(c1*exp(c2*t)+c3*exp(c4*t)+1)+aux_k;
    			if(value>0.99*k)permanente=true; //y(t)=k Valor final alcanzado SOLO PARA LTI 1ºorden
    		}
    		else
    		{
    			value=(k-aux_k)*(1-c5*exp(-raiz.real*t)*sin(raiz.imag*t+raiz.theta))+aux_k;
    		}
    }
}

/**
* @brief 
* @param 
*/
float Modelo::GetValue()
{
    return value+c0;//+Condiciones iniciales 
}

/**
* @brief 
* @param 
*/
void Modelo::StartModelo(float _t,float _k,float _v)
{
    t0=_t;//Tiempo de inicio
    state=true;
    permanente=false;
    k=_k;
    aux_k=value=_v;
}

/**
* @brief 
* @param 
*/
void Modelo::StopModelo()
{
    t0=value=0;
    state=false;
}

/**
* @brief 
* @param 
*/
const std::string Modelo::GetName()
{
    return m_name;
}

/**
* @brief 
* @param 
*/
bool Modelo::ModeloStarted()
{
    return state;
}

/**
* @brief 
* @param 
*/
bool Modelo::GetPermanente()
{
    return permanente;
}

/**
* @brief 
* @param 
*/
bool Modelo::Check_K(float _t,float new_k)
{
	if(new_k!=k)
	{
		StartModelo(_t,new_k,value);
		return true;
	}
	else
		return false;
}
