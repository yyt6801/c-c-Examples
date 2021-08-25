/****************************************************************************** */
/*	�ļ���	: Algorithm.h														*/
/*																				*/
/*	��  ��	: ͨ���㷨������													*/
/*																				*/
/*	�汾��ʷ��																	*/
/*	--------------------------------------------------------------------------	*/
/*	   �汾��|	 �� ��	  | ����  | �޸�ע��									*/
/*		1.00 | 2011-06-07 | �� �� |	��ʼ�汾									*/
/*																				*/
/*	--------------------------------------------------------------------------	*/
/*																				*/
/*						COPYRIGHT (C)  NERCAR of USTB							*/
/*																				*/
/****************************************************************************** */

#ifndef _ALGORITH_H_
#define _ALGORITH_H_


#include <math.h>
#include <float.h>

#pragma warning(push)
#pragma warning(disable: 4244)	//double -> float


class Algorithm
{

public:

	//
	// �ж������Ƿ���Ч
	//
	template<class TypeX, class Type>
    static inline bool IsValid(TypeX x, Type min, Type max)
    {
		const char *dt = typeid(x).name();
		if (!strncmp (dt, "float", 5) || !strncmp (dt, "double", 6))
		{
			if (_fpclass(x) < 8 || _fpclass(x) == 512)	
			{
				return  false;	//��Ч������
			}
		}

		return (x >= min && x <= max);	
	}

	//
	// �޷�����
	//
	template<class TypeX, class Type>
    static inline TypeX Limiter(TypeX x, Type min, Type max)
    {
		//��Ч����������
		const char *dt = typeid(x).name();
		if (!strncmp (dt, "float", 5) || !strncmp (dt, "double", 6))
		{
			if ( _fpclass(x) <    8 )	return  min;
			if ( _fpclass(x) == 512 )	return  max;	
		}

		if		(x < min)	return min;
		else if (x > max)	return max;
		else				return x;
	}

	//
	// �ж�xΪ���ż��
	//
	template<class Type>
    static inline bool IsEven(Type x)
    {
        return (x&1)?0:1;
    }
	template<class Type>
    static inline bool IsOdd(Type x)
    {
        return (x&1)?1:0;
    }

	//
	//	λ����
	//
	template<class Type>
    static inline void SetBit(Type& x, int n)
	{
		x |= (1<<n);
	}
	template<class Type>
    static inline void ClearBit(Type& x, int n)
	{
		x &= (~(1<<n));
	}
	template<class Type>
    static inline bool BitIsClear(Type x, int n)
	{
		return( (x & (1<<n)) == 0 );
	}
	template<class Type>
    static inline bool BitIsSet(Type x, int n)
	{
		return( !BitIsClear(x, n) );
	}

	//
	// �����㷨����������xa[]�е�һ�����ڻ����x��Ԫ��������
	//
	// ע�⣺Ҫ��xa[]ֵΪ��������
	//
	template<class Type>
    static inline int Search(const Type& x, const Type xa[], int n)
    {
		int i;

		for (i=0; i<n-1; i++)
		{
			if (xa[i] >= x)	break;
		}

		return i;
	}


	//
	// �����������СֵԪ�ص�����
	//
	template<class Type>
	static  inline int IndexOfMin(const Type xa[], int n)
	{
		int  i,j = 0;
		Type Min = xa[0];

		for (i = 1; i < n; i++)
		{
			if (xa[i] < Min)
			{
				Min = xa[i];
				j = i;
			}
		}

		return (j);
	}


	//
	// ������������ֵԪ�ص�����
	//
	template<class Type>
	static  inline int IndexOfMax(const Type xa[], int n)
	{
		int  i,j = 0;
		Type Max = xa[0];

		for (i = 1; i < n; i++)
		{
			if (xa[i] > Max)
			{
				Max = xa[i];
				j = i;
			}
		}

		return (j);
	}

    
	//
	// �����������Сֵ
	//
	template<class Type>
	static  inline Type Min(const Type xa[], int n)
	{
		int  i;
		Type Min = xa[0];

		for (i = 1; i < n; i++)
		{
			if (xa[i] < Min)
			{
				Min = xa[i];
			}
		}

		return (Min);
	}

	//
	// ������������ֵ
	//xa[10]={'12','34'..}
	//int a= Max(xa,10)
	template<class Type>
	static  inline Type Max(const Type xa[], int n)
	{
		int  i;
		Type Max = xa[0];

		for (i = 1; i < n; i++)
		{
			if (xa[i] > Max)
			{
				Max = xa[i];
			}
		}

		return (Max);
	}

	//
	// ���������ƽ��ֵ
	//
	template<class Type>
	static  inline Type Mean(const Type xa[], int n)
	{
		if (n <= 0)  return (Type(0));	//2012-7-13 add

		int  i;
		Type Mean = xa[0];

		for (i = 1; i < n; i++)
		{
			Mean += xa[i];
		}

		return Type(Mean/(1.0*n));
	}

	//
	// ���������Sigmaֵ
	//
	template<class Type>
	static  inline double Sigma(const Type xa[], int n)
	{
		int    i;
		Type   Mean  = MeanOf(xa, n);
		double Sigma = 0;

		for (i = 0; i < n; i++)
		{
			Sigma += (xa[i] - Mean) * (xa[i] - Mean);
		}

		if (n > 1)
		{
			Sigma /= n-1;

			if(Sigma > 0.0)
			{
				Sigma = sqrt(Sigma);
			}
		}

		return Sigma;
	}


	//
	// �ֶ����Բ�ֵ�㷨
	//
	// ע�⣺Ҫ��xa[]ֵΪ����
	//
	template<class TypeX, class TypeY>
    static TypeY LinearInterp(const TypeX& x, const TypeX xa[], const TypeY ya[], int n)
    {
		int left   = 0;     
		int right  = n - 1;

		if (n <= 1)
		{
			return ya[0];
		}
		else if (n > 2) 
		{   
			int desc = (xa[left] > xa[right]);  

			//�������
			if ( (!desc && x <= xa[left]) || (desc && x >= xa[left]) ) 
			{
				right = left + 1;   
			}
			//�Ҳ�����
			else if( (!desc && x >= xa[right]) || (desc && x <= xa[right]) )
			{
				left = right - 1;
			}
			//�����ڲ�ֵ
			else
			{    
				//����x���ڵ�����
				while (right > left+1)
				{   
					int middle = (left + right + 1) / 2;

					if ( (!desc && x > xa[middle]) || (desc && x < xa[middle]) )
					{
						left = middle;
					} 
					else
					{  
						right = middle;
					}
				}
			} 
		}

		if (xa[left] == xa[right])
		{
			return (ya[right]);
		}
		else if (xa[left] == x)
		{
			return (ya[left]);
		}
		else
		{
			//���Բ�ֵ
			return ( ya[left] + 
				1.0 * (ya[right]-ya[left]) / (xa[right]-xa[left])
				* (x - xa[left]) );
		}

   }

	//
	// �ֶ�ţ�ٲ�ֵ�㷨
	//
	// ע�⣺Ҫ��xa[]ֵΪ�ϸ񵥵�����
	//
	template<class TypeX, class TypeY>
    static TypeY NewtonInterp(const TypeX& x, const TypeX xa[], const TypeY ya[], int n)
    {
		int		i,j; 
		int		loop; 
		TypeY	y[2];			//�������ţ�ٲ�ֵ�Ľ��
		double	f1[3],f2[2];    //һ�ײ�ֺͶ��ײ��

		//��������������xֵ����������֮��
		if( n < 3 || x <= xa[0] || x >= xa[n-1] )
		{
			return (LinearInterp(x, xa, ya, n));
		}

		//����xa[]�е�һ�����ڻ����x��Ԫ������
		i = Search(x, xa, n);
		if( xa[i] == x )
		{
			return (ya[i]);
		}

		//��֤��xǰ�����1������
		i--;

		//x֮ǰ���ֻ��1������: xa[i]��x��xa[i+1]��xa[i+2]
		if( i <= 0 )
		{
			i = 0;
			loop = 2;
		}
		else
		{
			//��֤��x֮ǰ��2������
			i--;

			//x֮�����ֻ��һ������: xa[i]��xa[i+1]��x��xa[i+2]
			if( i >= n - 3 )
			{
				i = n - 3;
				loop = 2;
			}
			//xǰ�����2������: xa[i]��xa[i+1]��x��xa[i+2]��xa[i+3]
			else
			{
				loop = 3;
			}
		}

		//ִ��ţ�ٲ�ֵ
		for(j = 0; j < loop; j++)
		{
			f1[j] = 1.0 * (ya[i+j+1] - ya[i+j]) / ( xa[i+j+1] - xa[i+j]);

			if( j > 0 )
			{
				f2[j-1] = (f1[j] - f1[j-1]) / ( xa[i+j+1] - xa[i+j-1]);

				y[j-1]  = ya[i+j-1]; 
				y[j-1] += f1[j-1]*(x-xa[i+j-1]);
				y[j-1] += f2[j-1]*(x-xa[i+j-1])*(x-xa[i+j]);
			}

		}

		//���ִֻ����һ�������ţ�ٲ�ֵ
		if(loop == 2)
		{
			y[1] = y[0];
		}

		//�ۺ��������������ţ�ٲ�ֵ���
		return ( TypeY(y[0] + 
			1.0*(y[1] - y[0])/(xa[i+2] - xa[i+1])
			* (x - xa[i+1])) );

	}

	//
	// �����Է�����ĸ�˹��Ԫ�㷨 A * X = Y
	//
	// ע�⣺����a[n*n]��y[]���ܻ�ı䣬����A�������ȴ洢��a[n*n]������
	//
	template<class TypeX, class TypeY, class TypeA>
	static bool GaussElimination(TypeX x[], TypeA a[], TypeY y[], int n)
	{
		int		i, j, k;
		double  tmp;
	   
		// ������Խ���Ԫ��Ϊ0���н���
		for (i = 0; i < n; i++) 
		{    
			if ( fabs(a[i*n+i]) <= 1e-5 )
			{
				for (j = i + 1; j < n; j++) 
				{
					if (fabs(a[j*n+i]) <= 1e-5 )
						continue;

					for (k = 0; k < n; k++) 
					{
						tmp = a[i*n+k];
						a[i*n+k] = a[j*n+k];
						a[j*n+k] = tmp;
					}
					tmp  = y[i];
					y[i] = y[j];
					y[j] = tmp;
					break;
				}

				// �н��������Խ���Ԫ����Ϊ0
				if (fabs(a[j*n+i]) <= 1e-5 )
				{
					return false;
				}
			}
		}

		//��Ԫ
		for (k = 0; k < n-1; k++) 
		{
			for (i = k+1; i<n; i++)
			{
				tmp = 1.0 * a[i*n+k] / a[k*n+k];
				for (j = k+1; j<n; j++)
				{
					a[i*n+j] -= tmp * a[k*n+j];
				}
				y[i] -= tmp * y[k];
			}
		}

		//���
		x[n-1] = y[n-1]/a[(n-1)*n+n-1];
		for(i=n-2; i>=0; i--)
		{
			x[i] = y[i];
			for(j=i+1; j<n; j++)
			{
				x[i] -= a[i*n+j]*x[j];
			}
			x[i] /= a[i*n+i];
		}
	    
		return true;
	}

	//
	// ��Ԫ���Իع��㷨  y = a0 + a1 * x1 + a2 * x2 + ....+ am * xm
	//
	// ע�⣺����a[]��Ԫ�ظ���Ϊm+1, xi�����������ȴ洢��xm[n*m]�����У�nΪ��������
	//
	template<class TypeX, class TypeY, class TypeA>
    static bool MultiLinearRegress(TypeA a[], int m, const TypeX xm[], const TypeY ya[], int n)
    {
		int	   i, j, k;
		double *sum_x, sum_y;
		double sum_xx, sum_xy;
		double *lnn, *lny;
		double *b;
		bool   ret;

		sum_x	= new double[m];
		lnn		= new double[m*m];
		lny		= new double[m];
		b		= new double[m];

		//��ÿ�еĺ�
		for(i=0; i<m; i++)
		{
			sum_x[i] = 0;
			for(j=0; j<n; j++)
			{
				sum_x[i] += xm[j*m + i];
			}
		}
		sum_y = 0;
		for(j=0; j<n; j++)
		{
			sum_y += ya[j];
		}

		//�������淽����
		for(i=0; i<m; i++)
		{
			for(k=i; k<m; k++)
			{
				sum_xx = 0;
				for(j=0; j<n; j++)
				{
					sum_xx += xm[j*m + i]*xm[j*m + k];
				}
				lnn[i*m + k] = sum_xx - sum_x[k] * sum_x[i] / n;
				lnn[k*m + i] = lnn[i*m + k];
			}
			sum_xy = 0;
			for(j=0; j<n; j++)
			{
				sum_xy += xm[j*m + i]*ya[j];
			}
			lny[i] = sum_xy - sum_x[i] * sum_y / n;
		}

		//��ⷽ����
		if(GaussElimination(b, lnn, lny, m))
		{
			a[0] = sum_y;
			for(i=0; i<m; i++)
			{
				a[i+1] = b[i];
				a[0]  -= b[i]*sum_x[i];
			}
			a[0] /= 1.f * n;

			ret = true;
		}
		else
		{
			ret = false;
		}

		delete [] sum_x;
		delete [] lnn;
		delete [] lny;
		delete [] b;

		return ret;
	}

	//
	// ����ʽ�ع��㷨   y = a0 + a1 * x + a2 * x^2 + ....+ am * x^m
	//
	// ע�⣺����a[]��Ԫ�ظ���Ϊm+1
	//
	template<class TypeX, class TypeY, class TypeA>
    static bool PolyRegress(TypeA a[], int m, const TypeX xa[], const TypeY ya[], int n)
    {
		int	   i, j;
		double *xm;
		bool   ret;

		xm = new double[n*m];

		//������ʽ�ع�ת��Ϊ��Ԫ���Իع�
		for(i=0; i<n; i++)
		{
			xm[i*m + 0] = xa[i];
			for(j=1; j<m; j++)
			{
				xm[i*m + j] = xm[i*m + j-1] * xa[i];
			}
		}

		//��Ԫ���Իع�
		ret = MultiLinearRegress(a, m, xm, ya, n);

		delete [] xm;

		return ret;
	}
	
	//					    /b
	// ����������㷨   y = |  f(x) * dx
	//					    /a
	//
	#define EPSILON			0.001	//����
	#define MAX_INTER		10		//����������
	template<class TypeX, class TypeY>
	static TypeY RombergIntegral(TypeY (*fun)(TypeX x), TypeX a, TypeX b)
	{
		int		i, k;
		int		m, n;		
		double	h, s, q;
		double	p;			//pΪ������Ԫ�ص�ǰһ��Ԫ��(ͬһ��)
		double	y[MAX_INTER];
		double	ep;			

		//��ֵ
		h = b - a;
		y[0] = h * (fun(a) + fun(b))/2.0;
		m = 1; 
		n = 1; 

		//��������
		do
		{ 
			//��T2n
			p = 0.0;
			for(i = 0; i < n; i++)
			{ 
				p += fun(a + (i + 0.5) * h);
			}
			p *= h;
			p = (y[0] + p)/2.0;	//p -> T2n 

			//���m��Ԫ��
			s = 1.0;
			for (k = 1; k <= m; k++)
			{ 
				s *= 4.0;
				q = (s * p - y[k-1]) / (s - 1.0);
				y[k-1] = p; 
				p = q;
			}

			ep = fabs((q - y[m-1])/q); //���־���
			m++; 
			y[m-1] = q; 
			n *= 2;			//�������λ��ֵķֵ���
			h *= 0.5;

		}while ((ep >= EPSILON) && (m < MAX_INTER-1));

		return ((TypeY)q);
	}


};


#pragma warning(pop)

#endif //_ALGORITH_H_
