//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef FSUTILS_H
#define FSUTILS_H

#include "AEConfig.h"
#include "entry.h"
//#include "PrSDKAESupport.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_EffectCBSuites.h"
#include "AE_Macros.h"
#include "AEGP_SuiteHandler.h"
#if defined(PF_AE100_PLUG_IN_VERSION)
	#include "AEFX_SuiteHelper.h"
#else
	#include "PF_Suite_Helper.h"
#endif
#include "String_Utils.h"
#include "Param_Utils.h"
#include "Smart_Utils.h"

#ifdef AE_OS_WIN
	#include <Windows.h>
#endif


//xorShift
#define F_SRAND(s) (init_xorShift(s))
#define F_RAND() (xorShift()) 
#define F_RAND_MAX 0x7FFF

#define F_RAND_D() (xorShiftDouble())

#define F_RAND_D2(min,max) (min + ((max - min) * xorShiftDouble()))

#define F_RAND_D1()		(2 * xorShiftDouble() -1)

//C�̃��C�u����
//#define F_SRAND(s) srand(s);for(int b=0; b<100;b++) rand()
//#ifdef AE_OS_WIN
//	//#define F_RAND() (xorShift())
//	#define F_RAND() (rand())
//#else
//	#define F_RAND() (rand()>>16)
//
//#endif



#define F_RAND2(min,max) ((min) + (A_long)( (double)F_RAND()*((double)(max) - (double)(min) +1.0f )/(double)(1.0f+F_RAND_MAX))) 
#define F_RAND3(max) ((A_long)( (double)F_RAND()*((double)(max) +1.0f )/(1.0f+F_RAND_MAX) ) )

#define	FIX2FLT(X)	((double)(X) / 65536.0)
#define	FLT2FIX(F)	((PF_Fixed)((F) * 65536 + (((F) < 0) ? -0.5 : 0.5)))
#define F_ABS(x) ((x) >= 0 ? (x) : -(x))

//�ϐ��̌^�ϊ�

//-----------------------------------------------------------------------------------
inline A_u_char RoundByteLong(A_long x)
{
	A_long temp=x;
	if (temp<0)   temp=0;
	if (temp>PF_MAX_CHAN8) temp=PF_MAX_CHAN8;
	return (A_u_char)temp;
}
//-----------------------------------------------------------------------------------
inline A_u_char RoundByteFpLong(PF_FpLong x)
{
	PF_FpLong temp=x;
	if (temp<0)   temp=0;
	if (temp>PF_MAX_CHAN8) temp=PF_MAX_CHAN8;
	return (A_u_char)temp;
}
//-----------------------------------------------------------------------------------
inline A_u_char RoundByteFpShort(PF_FpShort x)
{
	PF_FpShort temp=x;
	if (temp<0)   temp=0;
	if (temp>PF_MAX_CHAN8) temp=PF_MAX_CHAN8;
	return (A_u_char)temp;
}
//-----------------------------------------------------------------------------------
inline A_u_char RoundByteDouble(double x)
{
	double temp = x;
	if (temp<0)   temp = 0;
	if (temp>PF_MAX_CHAN8) temp = PF_MAX_CHAN8;
	return (A_u_char)temp;
}
//-----------------------------------------------------------------------------------
inline A_u_short RoundShort(A_long x)
{
	A_long temp=x;
	if (temp<0)   temp=0;
	if (temp>PF_MAX_CHAN16) temp=PF_MAX_CHAN16;
	return (A_u_short)temp;
}
//-----------------------------------------------------------------------------------
inline A_u_short RoundShortFpLong(PF_FpLong x)
{
	PF_FpLong temp=x;
	if (temp<0)   temp=0;
	if (temp>PF_MAX_CHAN16) temp=PF_MAX_CHAN16;
	return (A_u_short)temp;
}
//-----------------------------------------------------------------------------------
inline PF_FpShort RoundFpShort(PF_FpShort x)
{
	PF_FpShort temp=x;
	if (temp<0)   temp=0;
	if (temp>32.0) temp=32.0;
	return temp;
}
//-----------------------------------------------------------------------------------
inline PF_FpShort RoundFpShortDouble(PF_FpLong x)
{
	double temp=x;
	if (temp<0)   temp=0;
	if (temp>32) temp=32.0;
	return (PF_FpShort)temp;
}
//-----------------------------------------------------------------------------------
inline PF_FpShort RoundFpShort2(PF_FpLong x)
{
	double temp = x;
	if (temp < 0)   temp = 0;
	if (temp > 1) temp = 1;
	return (PF_FpShort)temp;
}
//-----------------------------------------------------------------------------------
//***********************************************************************************
/*
	����
	xorShift�Ɋւ��Ă͈ȉ���HP�̋L�����Q�l�ɂ��܂����B

	������ɂԂ��`�����@2008�N10��31���@�����_��
	http://ogawa-sankinkoutai.seesaa.net/article/108848981.html

	����V���M�W�@Xorshift �̏�������
	http://d.hatena.ne.jp/gintenlabo/20100930/1285859540
*/

//***********************************************************************************
// xorShift�p�̃O���[�o���ϐ�
static A_u_long gSeed128[4];
//-------------------------------------------------------------------
static A_u_long xorShift()
{
	A_u_long t = ( gSeed128[ 0 ] ^ ( gSeed128[ 0 ] << 11 ) );
	gSeed128[ 0 ] = gSeed128[ 1 ];
	gSeed128[ 1 ] = gSeed128[ 2 ];
	gSeed128[ 2 ] = gSeed128[ 3 ];
	A_u_long ret =  (gSeed128[ 3 ] = ( gSeed128[ 3 ] ^ ( gSeed128[ 3 ] >> 19 ) ) ^ ( t ^ ( t >> 8 ) ) );
	ret = (ret>>16) & 0x7FFF;
	return ret;

}
//-------------------------------------------------------------------
static double xorShiftDouble()
{
	A_u_long t = ( gSeed128[ 0 ] ^ ( gSeed128[ 0 ] << 11 ) );
	gSeed128[ 0 ] = gSeed128[ 1 ];
	gSeed128[ 1 ] = gSeed128[ 2 ];
	gSeed128[ 2 ] = gSeed128[ 3 ];
	A_u_long ret =  (gSeed128[ 3 ] = ( gSeed128[ 3 ] ^ ( gSeed128[ 3 ] >> 19 ) ) ^ ( t ^ ( t >> 8 ) ) );
	ret = ret & 0x7FFFFFFF;

	return (double)ret / 0x7FFFFFFF;

}
//-------------------------------------------------------------------
static void init_xorShift(A_u_long s)
{
	A_u_long ss = s + 100;
	for ( A_u_long i=1; i<=4;i++)
	{
		gSeed128[ i - 1 ] = ss = 1812433253U * ( ss ^ ( ss >> 30 ) ) + i;
	}
}
//***********************************************************************************
/*
	�s�N�Z���ϊ�
*/
//***********************************************************************************
#define FS_CONVERT8TO16(A)		( (((A_long)(A) * PF_MAX_CHAN16) + PF_HALF_CHAN8) / PF_MAX_CHAN8 )
#define FS_CONVERT8TO32(A)      ((double)(long)((double)A*10000.0/(double)PF_MAX_CHAN8 + 0.5)/10000.0)
//#define FS_CONVERT8TO32(A)      ((double)(A)/PF_MAX_CHAN8)

#define FS_CONVERT16TO8(A)		( (((A_long)(A) * PF_MAX_CHAN8) + PF_HALF_CHAN16) / PF_MAX_CHAN16)
#define FS_CONVERT16TO32(A)      ((double)(long)((double)A*10000.0/(double)PF_MAX_CHAN16 + 0.5)/10000.0)
//#define FS_CONVERT16TO32(A)      ((double)(A)/PF_MAX_CHAN16)

#define FS_CONVERT32TO8(A)		(  (long)((A)*PF_MAX_CHAN8+0.5) )
#define FS_CONVERT32TO16(A)		(  FS_CONVERT8TO16(FS_CONVERT32TO8(A)) )
//#define FS_CONVERT32TO16(A)		( (long)(PF_MAX_CHAN16*(A)+0.5) )

#define FS_SHORT(A)				((double)(long)((double)A*10000.0 + 0.5)/10000.0)

//-----------------------------------------------------------------------------------
inline PF_Pixel16 CONV8TO16(PF_Pixel c)
{
	PF_Pixel16 r;
	r.alpha		= RoundShortFpLong(FS_CONVERT8TO16(c.alpha));
	r.red		= RoundShortFpLong(FS_CONVERT8TO16(c.red));
	r.green		= RoundShortFpLong(FS_CONVERT8TO16(c.green));
	r.blue		= RoundShortFpLong(FS_CONVERT8TO16(c.blue));
	return r;
}
#define C16TO8(A)		(RoundByteFpLong( (((A_long)(A) * PF_MAX_CHAN8) + PF_HALF_CHAN16) / PF_MAX_CHAN16))
//-----------------------------------------------------------------------------------
inline PF_Pixel CONV16TO8(PF_Pixel16 c)
{

	PF_Pixel r;
	r.alpha		= RoundByteFpLong(FS_CONVERT16TO8(c.alpha));
	r.red		= RoundByteFpLong(FS_CONVERT16TO8(c.red));
	r.green		= RoundByteFpLong(FS_CONVERT16TO8(c.green));
	r.blue		= RoundByteFpLong(FS_CONVERT16TO8(c.blue));
	return r;
}
//-------------------------------------------------------------------------------------------------
inline PF_PixelFloat CONV8TO32(PF_Pixel c)
{
	PF_PixelFloat r;
	r.alpha		= (PF_FpShort)(FS_CONVERT8TO32(c.alpha));
	r.red		= (PF_FpShort)(FS_CONVERT8TO32(c.red));
	r.green		= (PF_FpShort)(FS_CONVERT8TO32(c.green));
	r.blue		= (PF_FpShort)(FS_CONVERT8TO32(c.blue));
	return r;
}
//-------------------------------------------------------------------------------------------------
inline PF_PixelFloat CONV16TO32(PF_Pixel16 c)
{
	PF_PixelFloat r;
	r.alpha		= (PF_FpShort)(FS_CONVERT16TO32(c.alpha));
	r.red		= (PF_FpShort)(FS_CONVERT16TO32(c.red));
	r.green		= (PF_FpShort)(FS_CONVERT16TO32(c.green));
	r.blue		= (PF_FpShort)(FS_CONVERT16TO32(c.blue));
	return r;
}
//-------------------------------------------------------------------------------------------------
inline PF_Pixel CONV32TO8(PF_PixelFloat c)
{
	PF_Pixel r;
	r.alpha		= RoundByteLong(FS_CONVERT32TO8(c.alpha));
	r.red		= RoundByteLong(FS_CONVERT32TO8(c.red));
	r.green		= RoundByteLong(FS_CONVERT32TO8(c.green));
	r.blue		= RoundByteLong(FS_CONVERT32TO8(c.blue));
	return r;
}
//-------------------------------------------------------------------------------------------------
inline PF_Pixel16 CONV32TO16(PF_PixelFloat c)
{
	PF_Pixel16 r;
	r.alpha		= RoundShortFpLong(FS_CONVERT32TO16(c.alpha));
	r.red		= RoundShortFpLong(FS_CONVERT32TO16(c.red));
	r.green		= RoundShortFpLong(FS_CONVERT32TO16(c.green));
	r.blue		= RoundShortFpLong(FS_CONVERT32TO16(c.blue));
	return r;
}
//-------------------------------------------------------------------------------------------------
//*************************************************************************************************
//�s�N�Z���̔�r
//*************************************************************************************************
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix8(PF_Pixel s,PF_Pixel d)
{
	return ( (s.blue==d.blue)&&(s.green==d.green)&&(s.red==d.red) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix8Lv(PF_Pixel s,PF_Pixel d,A_u_char lv)
{
	return ( (F_ABS(s.blue-d.blue)<=lv)&&(F_ABS(s.green-d.green)<=lv)&&(F_ABS(s.red-d.red)<=lv) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix16(PF_Pixel16 s,PF_Pixel16 d)
{
	return ( (s.blue==d.blue)&&(s.green==d.green)&&(s.red==d.red) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix16Lv(PF_Pixel16 s,PF_Pixel16 d,A_u_short lv)
{
	return ( (F_ABS(s.blue-d.blue)<=lv)&&(F_ABS(s.green-d.green)<=lv)&&(F_ABS(s.red-d.red)<=lv) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix32(PF_PixelFloat s,PF_PixelFloat d)
{
	return ( (s.blue==d.blue)&&(s.green==d.green)&&(s.red==d.red) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix32Lv(PF_PixelFloat s,PF_PixelFloat d,PF_FpShort lv)
{
	return ( (F_ABS(s.blue-d.blue)<=lv)&&(F_ABS(s.green-d.green)<=lv)&&(F_ABS(s.red-d.red)<=lv) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix16_8(PF_Pixel16 s,PF_Pixel d)
{
	PF_Pixel ss;
	ss = CONV16TO8(s);
	return ( (ss.blue==d.blue)&&(ss.green==d.green)&&(ss.red==d.red) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix16_8Lv(PF_Pixel16 s,PF_Pixel d,A_u_char lv)
{
	PF_Pixel ss;
	ss = CONV16TO8(s);
	return ( (F_ABS(ss.blue-d.blue)<=lv)&&(F_ABS(ss.green-d.green)<=lv)&&(F_ABS(ss.red-d.red)<=lv) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix32_8Lv(PF_PixelFloat s,PF_Pixel d,A_u_char lv)
{
	PF_Pixel ss;
	ss = CONV32TO8(s);
	return ( (F_ABS(ss.blue-d.blue)<=lv)&&(F_ABS(ss.green-d.green)<=lv)&&(F_ABS(ss.red-d.red)<=lv) );
}
//-------------------------------------------------------------------------------------------------
inline PF_Boolean compPix32_8(PF_PixelFloat s,PF_Pixel d)
{
	PF_Pixel ss;
	ss = CONV32TO8(s);
	return ( (ss.blue==d.blue)&&(ss.green==d.green)&&(ss.red==d.red) );
}
//-------------------------------------------------------------------------------------------------
inline A_u_char Pixel8Level(PF_Pixel s)
{
	//77 150 29
	/*
	A_long v = (s.red * 77 + s.green + s.blue * 29) /256;
	if ( v>PF_MAX_CHAN8) v = PF_MAX_CHAN8;
	return (A_u_char)v;
	*/
		
	double v = ( 0.29891 * (double)s.red) + ( 0.58661 * (double)s.green) + ( 0.11448 * (double)s.blue);
	if ( v>PF_MAX_CHAN8) v = PF_MAX_CHAN8;
	return (A_u_char)v;
	
}
//-------------------------------------------------------------------------------------------------
inline A_u_long Pixel8LevelA(PF_Pixel s)
{
	//77 150 29
	/*
	A_long v = (s.red * 77 + s.green + s.blue * 29) /256;
	if ( v>PF_MAX_CHAN8) v = PF_MAX_CHAN8;
	return (A_u_char)v;
	*/
		
	double v = ( 0.29891 * (double)s.red) + ( 0.58661 * (double)s.green) + ( 0.11448 * (double)s.blue);
	if ( v>PF_MAX_CHAN8) v = PF_MAX_CHAN8;
	v = ((v+1) *256) + s.alpha;
	return (A_u_long)v;
	
}
//-------------------------------------------------------------------------------------------------
inline PF_FpShort Pixel8LevelFloat(PF_Pixel s)
{
	return (PF_FpShort)( (( 0.29891 * (double)s.red) + ( 0.58661 * (double)s.green) + ( 0.11448 * (double)s.blue))/PF_MAX_CHAN8);

}
//-------------------------------------------------------------------------------------------------
inline A_u_short Pixel16Level(PF_Pixel16 s)
{
	double v = ( 0.29891 * (double)s.red) + ( 0.58661 * (double)s.green) + ( 0.11448 * (double)s.blue);
	if ( v>PF_MAX_CHAN16) v = PF_MAX_CHAN16;
	return (A_u_short)v;

}
//-------------------------------------------------------------------------------------------------
inline PF_FpShort Pixel16LevelFloat(PF_Pixel16 s)
{
	return (PF_FpShort)( (( 0.29891 * (double)s.red) + ( 0.58661 * (double)s.green) + ( 0.11448 * (double)s.blue))/PF_MAX_CHAN16);
}
//-------------------------------------------------------------------------------------------------
inline PF_FpShort Pixel32Level(PF_PixelFloat s)
{
	PF_FpLong v = ( 0.29891 * s.red) + ( 0.58661 * s.green) + ( 0.11448 * s.blue);
	return (PF_FpShort)v;
}
//*************************************************************************************************
//AlphaBlend
inline PF_Pixel PixelBlend8(PF_Pixel src,PF_Pixel dst)
{
	PF_Pixel rr = {0,0,0,0};
	PF_Pixel ss = src;
	PF_Pixel dd = dst;

	if ( (ss.alpha == 0)||(dd.alpha==PF_MAX_CHAN8) ) return dd;
	if (dd.alpha == 0) return ss;
		
	A_long as2 = ( (PF_MAX_CHAN8+1) - dd.alpha) * ss.alpha >> 8;
	A_long ad2 = dd.alpha + as2;

	if (ad2>PF_MAX_CHAN8) ad2 = PF_MAX_CHAN8;

	if (ad2<=0) {
		//�O�̏��Z��h��
		return rr;
	}else{
		A_long r = ( dd.red   * dd.alpha + ss.red   * as2 );
		A_long g = ( dd.green * dd.alpha + ss.green * as2 );
		A_long b = ( dd.blue  * dd.alpha + ss.blue  * as2 );
		r/=ad2; g/=ad2; b/=ad2;

		if (r>PF_MAX_CHAN8) r = PF_MAX_CHAN8;
		if (g>PF_MAX_CHAN8) g = PF_MAX_CHAN8;
		if (b>PF_MAX_CHAN8) b = PF_MAX_CHAN8;

		rr.alpha	= (A_u_char)ad2;
		rr.red		= (A_u_char)r;
		rr.green	= (A_u_char)g;
		rr.blue		= (A_u_char)b;
		return rr;
	}
}
inline PF_Pixel16 PixelBlend16(PF_Pixel16 src,PF_Pixel16 dst)
{
	PF_Pixel16 rr = {0,0,0,0};
	PF_Pixel16 ss = src;
	PF_Pixel16 dd = dst;

	if ( (ss.alpha == 0)||(dd.alpha==PF_MAX_CHAN16) ) return dd;
	if (dd.alpha == 0) return ss;
	A_long as2 = ( PF_MAX_CHAN16 - dd.alpha) * ss.alpha >> 15;
	A_long ad2 = dd.alpha + as2;

	if (ad2>PF_MAX_CHAN16) ad2 = PF_MAX_CHAN16;

	if (ad2<=0) {
		return rr;
	}else{
		A_long r = ( dd.red   * dd.alpha + ss.red   * as2 );
		A_long g = ( dd.green * dd.alpha + ss.green * as2 );
		A_long b = ( dd.blue  * dd.alpha + ss.blue  * as2 );
		r/=ad2; g/=ad2; b/=ad2;

		if (r>PF_MAX_CHAN16) r = PF_MAX_CHAN16;
		if (g>PF_MAX_CHAN16) g = PF_MAX_CHAN16;
		if (b>PF_MAX_CHAN16) b = PF_MAX_CHAN16;

		rr.alpha	= (A_u_short)ad2;
		rr.red		= (A_u_short)r;
		rr.green	= (A_u_short)g;
		rr.blue		= (A_u_short)b;
		return rr;
	}
}
inline PF_PixelFloat PixelBlend32(PF_PixelFloat src,PF_PixelFloat dst)
{
	PF_PixelFloat rr = {0,0,0,0};
	PF_PixelFloat ss = src;
	PF_PixelFloat dd = dst;

	if ( (ss.alpha == 0)||(dd.alpha>=1.0) ) return dd;
	if (dd.alpha == 0) return ss;
	PF_FpShort as2 = ( 1 - dd.alpha) * ss.alpha;
	PF_FpShort ad2 = dd.alpha + as2;

	if (ad2>1.0) ad2 = 1.0;

	if (ad2<=0) {
		return rr;
	}else{
		PF_FpShort r = ( dd.red   * dd.alpha + ss.red   * as2 );
		PF_FpShort g = ( dd.green * dd.alpha + ss.green * as2 );
		PF_FpShort b = ( dd.blue  * dd.alpha + ss.blue  * as2 );
		r/=ad2; g/=ad2; b/=ad2;

		if (r>1.0) r = 1.0;
		if (g>1.0) g = 1.0;
		if (b>1.0) b = 1.0;

		rr.alpha	= ad2;
		rr.red		= r;
		rr.green	= g;
		rr.blue		= b;
		return rr;
	}
}

//*************************************************************************************************
//�~���v�Z
//*************************************************************************************************
inline PF_Fixed mm2px(PF_Fixed mm,PF_Fixed dpi)
{
	double ret;
	ret = ((double)mm/65536) * ((double)dpi/65536) / 25.4;
	return FLT2FIX(ret);
}
inline PF_Fixed px2mm(PF_Fixed px,PF_Fixed dpi)
{
	double ret;
	ret = ((double)px/65536) * 25.4 / ((double)dpi/65536);
	return FLT2FIX(ret);
}
//*************************************************************rot************************************
//�p�x�v�Z
//*************************************************************************************************

class CRotCalc
{
protected:
	PF_InData		*in_data;
	PF_Fixed		m_rot;
	PF_Fixed		m_length;
	PF_FixedPoint	m_pos;

public:
	//------------------------------
	void Init()
	{
		in_data = NULL;
		m_rot =
		m_length =
		m_pos.x =
		m_pos.y = 0;
	}
	//------------------------------
	CRotCalc(PF_InData *in_dataP)
	{
		Init();
		in_data = in_dataP;
	}
	//------------------------------
	PF_Fixed	rot() { return m_rot;}
	PF_Fixed	length() { return m_length;}
	PF_Fixed	x() { return m_pos.x;}
	PF_Fixed	y() { return m_pos.y;}
	PF_FixedPoint	pos() { return m_pos;}
	double		rotFLT() { return FIX2FLT(m_rot);}
	double		lengthFLT() { return FIX2FLT(m_length);}
	double		xFLT() { return FIX2FLT(m_pos.x);}
	double		yFLT() { return FIX2FLT(m_pos.y);}
	//------------------------------
	PF_Fixed RoundRot(PF_Fixed r)
	{
		PF_Fixed rr = r % (360L<<16);
		if ( rr<0) rr +=(360L<<16);
		return rr;
	}
	//------------------------------
	PF_FixedPoint SetRotLength(PF_Fixed r, PF_Fixed len)
	{
		m_rot = r;
		m_length = len;
		if (len != 0){
			PF_Fixed rr = RoundRot(r);
			double r2 = FIX2FLT(rr);
			double v2 = FIX2FLT(len);
			double x = 0;
			double y = 0;
			if ( (rr>=(0L<<16))&&(rr<(90L<<16)) ) {
				x =PF_SIN((PF_PI/180)*r2)*v2;
				y =PF_COS((PF_PI/180)*r2)*v2*-1;

			}else if ( (rr>=(90L<<16))&&(rr<(180L<<16)) ) {
				x =PF_COS((PF_PI/180)*(r2-90))*v2;
				y =PF_SIN((PF_PI/180)*(r2-90))*v2;

			}else if ( (rr>=(180L<<16))&&(rr<(270L<<16)) ) {
				x =PF_SIN((PF_PI/180)*(r2-180))*v2*-1;
				y =PF_COS((PF_PI/180)*(r2-180))*v2;

			}else if ( (rr>=(270L<<16))&&(rr<(360L<<16)) ) {
				x =PF_COS((PF_PI/180)*(r2-270))*v2*-1;
				y =PF_SIN((PF_PI/180)*(r2-270))*v2*-1;
			}
			m_pos.x = FLT2FIX(x);
			m_pos.y = FLT2FIX(y);
		}else{
			m_pos.x = 0;
			m_pos.y = 0;
		}
		return m_pos;
	}	
	//------------------------------
	PF_FixedPoint SetRot(PF_Fixed r) { return SetRotLength(r, m_length);}
	PF_FixedPoint SetLength(PF_Fixed len) { return SetRotLength(m_rot,len);}
	//------------------------------
	//------------------------------
	void SetPos(PF_Fixed x, PF_Fixed y)
	{
		m_pos.x = x;
		m_pos.y = y;
		if ( (x==0)&&(y==0) ){
			m_rot=0; m_length =0;
		}else{
			double xx = FIX2FLT(x);
			double yy = FIX2FLT(y);
			double rr = 90 - PF_ATAN2(yy,xx) * 180 /PF_PI;
			m_rot = FLT2FIX(rr) % (360L<<16);
			if (m_rot<0) m_rot += 360L<<16;

			xx = F_ABS(xx);
			xx = F_ABS(yy);
			double ll = PF_SQRT( PF_POW(xx,2) +PF_POW(yy,2));
			m_length = FLT2FIX(ll);
		}
	}
	//------------------------------
	void SetX(PF_Fixed x)
	{
		SetPos(x,m_pos.y);
	}
	//------------------------------
	void SetY(PF_Fixed y)
	{
		SetPos(m_pos.x,y);
	}
	//------------------------------
};
//*******************************************************
/*
inline void swapLong(A_long *s,A_long *d)
{
	A_long temp = *s;
	*s = *d;
	*d = temp;
}
*/
//*******************************************************
template<class T> 
inline void swapLong( T* s, T* d)
{
	T temp = *s;
	*s = *d;
	*d = temp;
}
	//*******************************************************
inline PF_Fixed RoundAngle360(PF_Fixed f)
{
	PF_Fixed ret = f;
	ret %= (360L<<16);
	if ( ret<0) ret += (360L<<16);
	return ret;
}
//*******************************************************
//*************************************************************rot************************************
//�p�x�v�Z
//*************************************************************************************************

class CRot
{
protected:
	PF_InData		*in_data;
	PF_FpLong		m_rot;
	PF_FpLong		m_length;
	PF_FpLong		m_x;
	PF_FpLong		m_y;

	
public:
	//------------------------------
	void Init()
	{
		in_data = NULL;
		m_rot =
			m_length =
			m_x =
			m_y = 0;
	}
	//------------------------------
	CRot(PF_InData *in_dataP)
	{
		Init();
		in_data = in_dataP;
	}
	//------------------------------
	PF_FpLong	rot() { return m_rot; }
	PF_FpLong	length() { return m_length; }
	PF_FpLong	x() { return m_x; }
	PF_FpLong	y() { return m_y; }
	//------------------------------
	static PF_FpLong RoundRot(PF_FpLong r)
	{
		A_long rr = (A_long)(r * 65536 +0.5);
		rr = rr % (360*65536);
		if (rr < 0) rr += (360 * 65536);
		return (PF_FpLong)rr/65536;
	}
	//------------------------------
	void SetRotLength(PF_FpLong r, PF_FpLong len)
	{
		m_rot = r;
		m_length = len;
		if (len != 0) {
			PF_FpLong rr = RoundRot(r);
			double r2 = rr;
			double v2 = len;
			double x = 0;
			double y = 0;
			if ((rr >= 0.0) && (rr < 90.0)) {
				x = PF_SIN((PF_PI / 180)*r2)*v2;
				y = PF_COS((PF_PI / 180)*r2)*v2*-1;

			}
			else if ((rr >= 90) && (rr < 180)) {
				x = PF_COS((PF_PI / 180)*(r2 - 90))*v2;
				y = PF_SIN((PF_PI / 180)*(r2 - 90))*v2;

			}
			else if ((rr >= 180) && (rr < 270)) {
				x = PF_SIN((PF_PI / 180)*(r2 - 180))*v2*-1;
				y = PF_COS((PF_PI / 180)*(r2 - 180))*v2;

			}
			else if ((rr >= 270) && (rr < 360)) {
				x = PF_COS((PF_PI / 180)*(r2 - 270))*v2*-1;
				y = PF_SIN((PF_PI / 180)*(r2 - 270))*v2*-1;
			}
			m_x = x;
			m_y = y;
		}
		else {
			m_x = 0;
			m_y = 0;
		}
	}
	//------------------------------
	void SetRot(PF_FpLong r) { return SetRotLength(r, m_length); }
	void SetLength(PF_FpLong len) { return SetRotLength(m_rot, len); }
	//------------------------------
	//------------------------------
	void SetXY(PF_FpLong x, PF_FpLong y)
	{
		m_x = x;
		m_y = y;
		if ((x == 0) && (y == 0)) {
			m_rot = 0; m_length = 0;
		}
		else {
			double xx = x;
			double yy = y;
			double rr = 90 - PF_ATAN2(yy, xx) * 180 / PF_PI;
			m_rot = RoundRot( rr);

			double ll = PF_SQRT(PF_POW(xx, 2) + PF_POW(yy, 2));
			m_length = ll;
		}
	}
	//------------------------------
	void SetX(PF_FpLong x)
	{
		SetXY(x, m_y);
	}
	//------------------------------
	void SetY(PF_FpLong y)
	{
		SetXY(m_x, y);
	}
	//------------------------------
};
#endif