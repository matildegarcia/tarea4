#include "../include/fecha.h"

struct rep_fecha
{
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio)
{

    TFecha nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;

    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha)
{
    delete fecha;
    fecha = NULL;
}

void imprimirTFecha(TFecha fecha)
{
    if (fecha != NULL)
    {
        printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);
    }
}

void aumentarTFecha(TFecha &fecha, nat dias)
{
    while (dias > 0)
    {
        nat diasEnMes;

        switch (fecha->mes)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            diasEnMes = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            diasEnMes = 30;
            break;

        case 2:
            if ((fecha->anio % 4 == 0 && fecha->anio % 100 != 0) || fecha->anio % 400 == 0)
            {
                diasEnMes = 29;
            }
            else
            {
                diasEnMes = 28;
            }
            break;

        default:
            break;
        }

        if (fecha->dia + dias <= diasEnMes)
        {
            fecha->dia += dias;
            break;
        }
        else
        {
            dias -= (diasEnMes - fecha->dia + 1);
            fecha->dia = 1;
            fecha->mes++;

            if (fecha->mes > 12)
            {
                fecha->mes = 1;
                fecha->anio++;
            }
        }
    }
}

int compararTFechas(TFecha fecha1, TFecha fecha2)
{
    int res = 0;

    if (fecha1->anio > fecha2->anio)
    {
        res = 1;
    }
    else if (fecha1->anio < fecha2->anio)
    {
        res = -1; 
    }
    else
    {
        if (fecha1->mes > fecha2->mes)
        {
            res = 1; 
        }
        else if (fecha1->mes < fecha2->mes)
        {
            res = -1; 
        }
        else
        {
            if (fecha1->dia > fecha2->dia)
            {
                res = 1; 
            }
            else if (fecha1->dia < fecha2->dia)
            {
                res = -1; 
            }
        }
    }

    return res;
}

TFecha copiarTFecha(TFecha fecha)
{
  
    TFecha nuevaFecha = crearTFecha(fecha->dia, fecha->mes, fecha->anio);
    return nuevaFecha;
}