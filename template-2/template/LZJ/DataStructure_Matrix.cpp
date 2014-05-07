#include "..\CommonHeadings.cpp"

namespace DataStructure {
	template<typename ValueType = int>
	struct Matrix {
		std::vector < std::vector < ValueType > > element;
		
		inline friend Matrix <ValueType> operator * (const Matrix <ValueType>& A, const Matrix <ValueType>& B) {
			int Ax = (int)A.element.size () - 1, Ay = (int)A.element [0].size () - 1;
			int Bx = (int)B.element.size () - 1, By = (int)B.element [0].size () - 1;
			
			#ifdef ASSERT_AVAILABLE
				assert (Ay == Bx);
			#endif
			
			Matrix <ValueType> C; C.resize (Ax, By);
			
			for (int i = 1; i <= Ax; ++i)
				for (int j = 1; j <= By; ++j)
					for (int k = 1; k <= Ay; ++k)
						C.element [i][j] += A.element [i][k] * B.element [k][j];
			
			return C;
		}
		
		inline friend Matrix <ValueType> operator + (const Matrix <ValueType>& A, const Matrix <ValueType>& B) {
			int Ax = (int)A.element.size () - 1, Ay = (int)A.element [0].size () - 1;
			int Bx = (int)B.element.size () - 1, By = (int)B.element [0].size () - 1;
			
			#ifdef ASSERT_AVAILABLE
				assert (Ax == Bx && Ay == By);
			#endif
			
			Matrix <ValueType> C; C.resize (Ax, Ay);
			
			for (int i = 1; i <= Ax; ++i)
				for (int j = 1; j <= Ay; ++j)
					C.element [i][j] = A.element [i][j] + B.element [i][j];
			
			return C;
		}
		
		inline Matrix <ValueType>& operator += (const Matrix <ValueType>& A) {
			(*this) = (*this) + A;
			return *this;
		}
		
		inline void resize (int N, int M) {
			element.clear ();
			
			element.resize (N + 1);
			for (int i = 0; i <= N; ++i)
				element [i].resize (M + 1);
		}
		
		inline std::vector < ValueType >& operator [] (int i) {
			#ifdef ASSERT_AVAILABLE
				assert (i > 0 && i < (int)element [0].size ());
			#endif
			
			return element [i];
		}
		
		inline Matrix () {
			resize (0, 0);
		}
		
		inline Matrix (int N, int M) {
			#ifdef ASSERT_AVAILABLE
				assert (N > 0 && M > 0);
			#endif
			
			resize (N, M);
		}
	};
}

DataStructure::Matrix<int> A, B;

int main () {
	A.resize (2, 2);
	A [1][1] = 1, A [1][2] = 1;
	A [2][1] = 1, A [2][2] = 1;
	
	B = A * A;
	
	for (int i = 1; i <= 2; ++i)
		for (int j = 1; j <= 2; ++j)
			printf ("%d%s", B [i][j], (j < 2) ? " " : "\n");
	
	return 0;
}

