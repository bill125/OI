namespace DataStructure {
	template<typename ValueType = long long>
	struct ModInteger {
		ValueType value, modular;
		
		inline friend ModInteger < ValueType > operator + (const ModInteger < ValueType >& A, const ModInteger < ValueType >& B) {
			#ifdef ASSERT_AVAILABLE
				assert (A.modular == B.modular);
			#endif
			
			ValueType modular = A.modular;
			ValueType value = A.value + B.value;
			
			if (value >= modular)
				value -= modular;
			
			return ModInteger < ValueType > (value, modular);
		}
		
		inline friend ModInteger < ValueType > operator - (const ModInteger < ValueType >& A, const ModInteger < ValueType >& B) {
			#ifdef ASSERT_AVAILABLE
				assert (A.modular == B.modular);
			#endif
			
			ValueType modular = A.modular;
			ValueType value = A.value - B.value;
			
			if (value < 0)
				value += modular;
			
			return ModInteger < ValueType > (value, modular);
		}
		
		inline friend ModInteger < ValueType > operator * (const ModInteger < ValueType >& A, const ModInteger < ValueType >& B) {
			#ifdef ASSERT_AVAILABLE
				assert (A.modular == B.modular);
			#endif
			
			ValueType modular = A.modular;
			ValueType value = A.value * B.value % modular;
			
			return ModInteger < ValueType > (value, modular);
		}
		
		inline friend ModInteger < ValueType > operator / (const ModInteger < ValueType >& A, const ModInteger < ValueType >& B) {
			#ifdef ASSERT_AVAILABLE
				assert (A.modular == B.modular);
			#endif
			
			ValueType modular = A.modular;
//			ValueType value = A.value * NumberTheory::inversion (B.value, modular) % modular;
			
			return ModInteger < ValueType > (value, modular);
		}
		
		inline ModInteger < ValueType >& operator += (const ModInteger < ValueType >& A) {
			(*this) = (*this) + A;
			return *this;
		}
		
		inline ModInteger < ValueType >& operator -= (const ModInteger < ValueType >& A) {
			(*this) = (*this) - A;
			return *this;
		}
		
		inline ModInteger < ValueType >& operator *= (const ModInteger < ValueType >& A) {
			(*this) = (*this) * A;
			return *this;
		}
		
		inline ModInteger < ValueType >& operator /= (const ModInteger < ValueType >& A) {
			(*this) = (*this) / A;
			return *this;
		}
		
		inline friend bool operator == (const ModInteger < ValueType >& A, const ModInteger < ValueType >& B) {
			return A.value == B.value;
		}
		
		inline friend bool operator != (const ModInteger < ValueType >& A, const ModInteger < ValueType >& B) {
			return A.value != B.value;
		}
		
		inline ModInteger (const ValueType& _value = 0, const ValueType& _modular = 1000000007) {
			_value %= _modular;
			
			if (_value < 0)
				_value += _modular;
			
			value = _value, modular = _modular;
		}
	};
}
