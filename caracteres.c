#include "caracteres.h"

#include <string.h>

enum caracter {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,CERO,UNO,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,OCHO,NUEVE,ARR,ABJ,DER,IZQ,ESP};

const float caracter_a[7][2] = {
	{0, 0},
	{0, 4},
	{2, 6},
	{4, 4},
	{4, 0},
	{4, 2},
	{0, 2}
};

const float caracter_b[12][2] = {
	{0, 3},
	{0, 6},
	{3, 6},
	{4, 5},
	{4, 4},
	{3, 3},
	{0, 3},
	{0, 0},
	{3, 0},
	{4, 1},
	{4, 2},
	{3, 3},
};

const float caracter_c[4][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
};

const float caracter_d[7][2] = {
	{0, 0},
	{0, 6},
	{2, 6},
	{4, 4},
	{4, 2},
	{2, 0},
	{0, 0}
};

const float caracter_e[7][2] = {
	{4, 0},
	{0, 0},
	{0, 3},
	{3, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_f[6][2] = {
	{0, 0},
	{0, 3},
	{3, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_g[7][2] = {
	{2, 2},
	{4, 2},
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 4},
};

const float caracter_h[6][2] = {
	{0, 0},
	{0, 6},
	{0, 3},
	{4, 3},
	{4, 6},
	{4, 0},
};

const float caracter_i[6][2] = {
	{0, 0},
	{4, 0},
	{2, 0},
	{2, 6},
	{4, 6},
	{0, 6},
};

const float caracter_j[4][2] = {
	{0, 2},
	{2, 0},
	{4, 0},
	{4, 6},
};

const float caracter_k[6][2] = {
	{0, 0},
	{0, 6},
	{0, 3},
	{3, 6},
	{0, 3},
	{3, 0},
};

const float caracter_l[3][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
};

const float caracter_m[5][2] = {
	{0, 0},
	{0, 6},
	{2, 4},
	{4, 6},
	{4, 0},
};

const float caracter_n[4][2] = {
	{0, 0},
	{0, 6},
	{4, 0},
	{4, 6},
};

const float caracter_o[5][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 0},
};

const float caracter_p[5][2] = {
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
};

const float caracter_q[9][2] = {
	{2, 2},
	{3, 1},
	{2, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 2},
	{3, 1},
	{4, 0},
};

const float caracter_r[7][2] = {
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
	{1, 3},
	{4, 0},
};

const float caracter_s[6][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_t[4][2] = {
	{2, 0},
	{2, 6},
	{4, 6},
	{0, 6},
};

const float caracter_u[4][2] = {
	{0, 6},
	{0, 0},
	{4, 0},
	{4, 6},
};

const float caracter_v[3][2] = {
	{0, 6},
	{2, 0},
	{4, 6},
};

const float caracter_w[5][2] = {
	{0, 6},
	{0, 0},
	{2, 2},
	{4, 0},
	{4, 6},
};

const float caracter_x[5][2] = {
	{0, 0},
	{4, 6},
	{2, 3},
	{0, 6},
	{4, 0},
};

const float caracter_y[5][2] = {
	{0, 6},
	{2, 4},
	{4, 6},
	{2, 4},
	{2, 0},
};

const float caracter_z[4][2] = {
	{0, 6},
	{4, 6},
	{0, 0},
	{4, 0},
};

const float caracter_0[5][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 0},
};

const float caracter_1[2][2] = {
	{2, 0},
	{2, 6},
};

const float caracter_2[6][2] = {
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
	{0, 0},
	{4, 0},
};

const float caracter_3[7][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{4, 3},
	{4, 6},
	{0, 6},
};

const float caracter_4[5][2] = {
	{0, 6},
	{0, 3},
	{4, 3},
	{4, 6},
	{4, 0},
};

const float caracter_5[6][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const float caracter_6[5][2] = {
	{0, 6},
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
};

const float caracter_7[3][2] = {
	{0, 6},
	{4, 6},
	{4, 0},
};

const float caracter_8[7][2] = {
	{0, 3},
	{0, 6},
	{4, 6},
	{4, 0},
	{0, 0},
	{0, 3},
	{4, 3},
};

const float caracter_9[5][2] = {
	{4, 0},
	{4, 6},
	{0, 6},
	{0, 3},
	{4, 3},
};

const float caracter_derecha[5][2] = {
	{0, 3},
	{12, 3},
	{9, 5},
	{9, 1},
	{12, 3},
};

const float caracter_izquierda[5][2] = {
	{12, 3},
	{0, 3},
	{3, 5},
	{3, 1},
	{0, 3},
};

const float caracter_arriba[5][2] = {
	{5, -2},
	{5, 10},
	{3, 7},
	{7, 7},
	{5, 10},
};

const float caracter_abajo[5][2] = {
	{5, 10},
	{5, -2},
	{3, 1},
	{7, 1},
	{5, -2},
};

const float caracter_espacio[1][2] = {
	{0, 0},
};

const char letras[]= {
	[a]='a',
	[b]='b',
	[c]='c',
	[d]='d',
	[e]='e',
	[f]='f',
	[g]='g',
	[h]='h',
	[i]='i',
	[j]='j',
	[k]='k',
	[l]='l',
	[m]='m',
	[n]='n',
	[o]='o',
	[p]='p',
	[q]='q',
	[r]='r',
	[s]='s',
	[t]='t',
	[u]='u',
	[v]='v',
	[w]='w',
	[x]='x',
	[y]='y',
	[z]='z',

	[CERO]='0',
	[UNO]='1',
	[DOS]='2',
	[TRES]='3',
	[CUATRO]='4',
	[CINCO]='5',
	[SEIS]='6',
	[SIETE]='7',
	[OCHO]='8',
	[NUEVE]='9',

	[IZQ]='<',
	[DER]='>',
	[ARR]='^',
	[ABJ]='V',

	[ESP]=' ',
};

const float (*caracteres[])[2]= {
	[a]=caracter_a,
	[b]=caracter_b,
	[c]=caracter_c,
	[d]=caracter_d,
	[e]=caracter_e,
	[f]=caracter_f,
	[g]=caracter_g,
	[h]=caracter_h,
	[i]=caracter_i,
	[j]=caracter_j,
	[k]=caracter_k,
	[l]=caracter_l,
	[m]=caracter_m,
	[n]=caracter_n,
	[o]=caracter_o,
	[p]=caracter_p,
	[q]=caracter_q,
	[r]=caracter_r,
	[s]=caracter_s,
	[t]=caracter_t,
	[u]=caracter_u,
	[v]=caracter_v,
	[w]=caracter_w,
	[x]=caracter_x,
	[y]=caracter_y,
	[z]=caracter_z,

	[CERO]=caracter_0,
	[UNO]=caracter_1,
	[DOS]=caracter_2,
	[TRES]=caracter_3,
	[CUATRO]=caracter_4,
	[CINCO]=caracter_5,
	[SEIS]=caracter_6,
	[SIETE]=caracter_7,
	[OCHO]=caracter_8,
	[NUEVE]=caracter_9,

	[IZQ]=caracter_izquierda,
	[DER]=caracter_derecha,
	[ARR]=caracter_arriba,
	[ABJ]=caracter_abajo,

	[ESP]=caracter_espacio,
};

const size_t tamanios[]={
	[a]=7,
	[b]=12,
	[c]=4,
	[d]=7,
	[e]=7,
	[f]=6,
	[g]=7,
	[h]=6,
	[i]=6,
	[j]=4,
	[k]=6,
	[l]=3,
	[m]=5,
	[n]=4,
	[o]=5,
	[p]=5,
	[q]=9,
	[r]=7,
	[s]=6,
	[t]=4,
	[u]=4,
	[v]=3,
	[w]=5,
	[x]=5,
	[y]=5,
	[z]=4,

	[CERO]=5,
	[UNO]=2,
	[DOS]=6,
	[TRES]=7,
	[CUATRO]=5,
	[CINCO]=6,
	[SEIS]=5,
	[SIETE]=3,
	[OCHO]=7,
	[NUEVE]=5,

	[IZQ]=5,
	[DER]=5,
	[ARR]=5,
	[ABJ]=5,

	[ESP]=1,
};

size_t pos_caracter_polilinea(char letra){
	size_t cantidad = sizeof(caracteres) / sizeof(caracteres[0]);
	for(size_t i = 0; i < cantidad; i++){
		if(letras[i] == letra){
			return tamanios[i];
		}
	}
	return cantidad;
}

size_t tamanio_polilinea(char letra){
	size_t cantidad = sizeof(caracteres) / sizeof(caracteres[0]);
	for(size_t i = 0; i < cantidad; i++){
		if(letras[i] == letra){
			return i;
		}
	}
	return cantidad;
}
